#include "gpg/nearby_connections.h"

#include "NearbyConnectionsScene.hpp"
#include "Utils.h"

#include "QuestScene.h" // prev scene

using namespace cocos2d;

cocos2d::Scene *NearbyConnectionsScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = NearbyConnectionsScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool NearbyConnectionsScene::init()
{
    if(!BaseScene::init())
    {
        return false;
    }

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    {
        CCLOG("Nearby is not support ios");
        return false;
    }
#endif

    server_id = "com.sdkbox.hugo.test.gpg.nearby";
    msg_adverstising = "this is a msg from adverstising";
    msg_discovery = "this is a msg from discovery";
    
    gpg::NearbyConnections::Builder* _builder = new gpg::NearbyConnections::Builder();
    
    _builder->SetDefaultOnLog( gpg::LogLevel::VERBOSE );
    _builder->SetServiceId( server_id );
    _builder->SetOnInitializationFinished([this](gpg::InitializationStatus status) {
        if (gpg::InitializationStatus::VALID == status) {
            this->miStartAdvertising->setVisible(true);
            this->miStartDiscovery->setVisible(true);
        }
    });
    
    nearby_conn = _builder->Create( *CreatePlatformConfiguration("").get() );

    delete _builder;

    
    Size size = Director::getInstance()->getWinSize();
    std::string defaultFont("arial.ttf");
    
    setTitle("NearbyConnections");
    
    miStartAdvertising = MenuItemFont::create("StartAdvertising", CC_CALLBACK_1(NearbyConnectionsScene::StartAdvertising, this));
    miStopAdvertising = MenuItemFont::create("StopAdvertising", CC_CALLBACK_1(NearbyConnectionsScene::StopAdvertising, this));
    miStartDiscovery = MenuItemFont::create("StartDiscovery", CC_CALLBACK_1(NearbyConnectionsScene::StartDiscovery, this));
    miStopDiscovery = MenuItemFont::create("StopDiscovery", CC_CALLBACK_1(NearbyConnectionsScene::StopDiscovery, this));
    miDisconnect = MenuItemFont::create("Disconnect", CC_CALLBACK_1(NearbyConnectionsScene::Disconnect, this));
    miStop = MenuItemFont::create("Stop", CC_CALLBACK_1(NearbyConnectionsScene::Stop, this));

    Menu* menu =
    Menu::create(
                 miStartAdvertising,
                 miStartAdvertising,
                 miStartDiscovery,
                 miStopDiscovery,
                 miDisconnect,
                 miStop,
                 nullptr
                 );
    
    menu->alignItemsVerticallyWithPadding(5);
    menu->setPosition(size.width/2, size.height/2 + 40);
    addChild(menu);
    
    miStartAdvertising->setVisible(false);
    miStartAdvertising->setVisible(false);
    miStartDiscovery->setVisible(false);
    miStopDiscovery->setVisible(false);
    miDisconnect->setVisible(false);
    miStop->setVisible(false);
    
    return true;
}

void NearbyConnectionsScene::onPrevScene(cocos2d::Ref *sender)
{
    Director::getInstance()->replaceScene(QuestScene::createScene());
}

void NearbyConnectionsScene::onNextScene(cocos2d::Ref *sender)
{
    BaseScene::onNextScene(sender);
}

void NearbyConnectionsScene::StartAdvertising(cocos2d::Ref *sender) {
    
    miStartAdvertising->setVisible(false);
    miStartDiscovery->setVisible(false);

    std::vector<gpg::AppIdentifier> appIdentifier;
    gpg::AppIdentifier app;
    app.identifier = server_id;
    appIdentifier.push_back(app);
    nearby_conn->StartAdvertising("",
                                  appIdentifier,
                                  gpg::Duration(0),
                                  [this](int64_t client_id, gpg::StartAdvertisingResult const &result) {
                                      if (gpg::StartAdvertisingResult::StatusCode::SUCCESS == result.status) {
                                          CCLOG("Start Advertising Success");
                                      } else {
                                          CCLOG("Start Advertising Failed:%d", result.status);
                                          this->miStartAdvertising->setVisible(true);
                                          this->miStartDiscovery->setVisible(true);
                                      }
                                  },
                                  [this](int64_t client_id, gpg::ConnectionRequest const &request) {
                                      std::vector<uint8_t> payload;
                                      this->nearby_conn->AcceptConnectionRequest(request.remote_endpoint_id, payload, this);
                                      
                                      payload = std::vector<uint8_t>(this->msg_adverstising.begin(), this->msg_adverstising.end());
                                      this->nearby_conn->SendReliableMessage(request.remote_endpoint_id, payload);
                                  });
}

void NearbyConnectionsScene::StopAdvertising(cocos2d::Ref *sender) {
    nearby_conn->StopAdvertising();
}

void NearbyConnectionsScene::StartDiscovery(cocos2d::Ref *sender) {
    nearby_conn->StartDiscovery(server_id, gpg::Duration(0), this);
}

void NearbyConnectionsScene::StopDiscovery(cocos2d::Ref *sender) {
    nearby_conn->StopDiscovery(server_id);
}

void NearbyConnectionsScene::Disconnect(cocos2d::Ref *sender) {
    auto remote_endpoint_id = ""; //TODO need use meaning endpoint id
    nearby_conn->Disconnect(remote_endpoint_id);
}

void NearbyConnectionsScene::Stop(cocos2d::Ref *sender) {
    nearby_conn->Stop();
}

//gpg::IMessageListener
void NearbyConnectionsScene::OnMessageReceived(int64_t client_id,
                                               std::string const &remote_endpoint_id,
                                               std::vector<uint8_t> const &payload,
                                               bool is_reliable) {
    std::string msg = std::string(payload.begin(), payload.end());
    CCLOG("Rev Msg:%s", msg.c_str());
}

void NearbyConnectionsScene::OnDisconnected(int64_t client_id,
                                            std::string const &remote_endpoint_id) {
    CCLOG("Disconnect:%s", remote_endpoint_id.c_str());
}

//gpg::IEndpointDiscoveryListener
void NearbyConnectionsScene::OnEndpointFound(int64_t client_id, gpg::EndpointDetails const &endpoint_details) {
    std::vector<uint8_t> payload;
    nearby_conn->SendConnectionRequest("",
                                       endpoint_details.endpoint_id,
                                       payload,
                                       [this](int64_t client_id, gpg::ConnectionResponse const &response) {
                                           if (gpg::ConnectionResponse::StatusCode::ACCEPTED == response.status) {
                                               std::vector<uint8_t> payload(this->msg_discovery.begin(), this->msg_discovery.end());
                                               this->nearby_conn->SendReliableMessage(response.remote_endpoint_id, payload);
                                           } else {
                                               CCLOG("Connect Failed:%d", response.status);
                                           }
                                       },
                                       this);
}

void NearbyConnectionsScene::OnEndpointLost(int64_t client_id, std::string const &remote_endpoint_id) {
    CCLOG("Endpoint Lost:%s", remote_endpoint_id.c_str());
}

