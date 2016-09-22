#pragma once

#include "BaseScene.h"

#include "gpg/nearby_connections.h"

class NearbyConnectionsScene : public BaseScene, public gpg::IMessageListener, public gpg::IEndpointDiscoveryListener {
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init() override;

    CREATE_FUNC(NearbyConnectionsScene);
    
protected:
    
    virtual void onPrevScene(cocos2d::Ref *sender) override;
    
    virtual void onNextScene(cocos2d::Ref *sender) override;
    
    void StartAdvertising(cocos2d::Ref *sender);
    void StopAdvertising(cocos2d::Ref *sender);
    void StartDiscovery(cocos2d::Ref *sender);
    void StopDiscovery(cocos2d::Ref *sender);
    void Disconnect(cocos2d::Ref *sender);
    void Stop(cocos2d::Ref *sender);
    
    //gpg::IMessageListener
    void OnMessageReceived(int64_t client_id, std::string const &remote_endpoint_id, std::vector<uint8_t> const &payload, bool is_reliable) override;
    void OnDisconnected(int64_t client_id, std::string const &remote_endpoint_id) override;

    //gpg::IEndpointDiscoveryListener
    virtual void OnEndpointFound(int64_t client_id, gpg::EndpointDetails const &endpoint_details) override;
    virtual void OnEndpointLost(int64_t client_id, std::string const &remote_endpoint_id) override;

protected:
    std::unique_ptr<gpg::NearbyConnections> nearby_conn;
    std::string server_id;
    std::string msg_adverstising;
    std::string msg_discovery;
    
    cocos2d::MenuItem* miStartAdvertising;
    cocos2d::MenuItem* miStopAdvertising;
    cocos2d::MenuItem* miStartDiscovery;
    cocos2d::MenuItem* miStopDiscovery;
    cocos2d::MenuItem* miDisconnect;
    cocos2d::MenuItem* miStop;

};
