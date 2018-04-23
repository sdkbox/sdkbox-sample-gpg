#include "SaveGameScene.h"
#include "Utils.h"
#include "LeaderboardScene.h"

using namespace json98;
using namespace cocos2d;


cocos2d::Scene *SaveGameScene::createScene()
{
    auto scene = Scene::create();

    auto layer = SaveGameScene::create();

    scene->addChild(layer);

    return scene;
}

bool SaveGameScene::init()
{
    if(!BaseScene::init())
    {
        return false;
    }

    Size size = Director::getInstance()->getWinSize();
    std::string defaultFont("arial.ttf");
    int defaultFontSize = 32;
    float lbl_offset = -120;

    _game_data["player_name"] = "Player1";
    _game_data["level"] = 1;
    _game_data["gold"] = 0;

    setTitle("SaveGame");

    auto ui_node = Node::create();
    ui_node->setPosition(Vec2(size.width/2 - 100, size.height/2));
    addChild(ui_node);

    auto lbl_name = Label::create("Name:", defaultFont, defaultFontSize);
    lbl_name->setPosition(lbl_offset, 40);
    ui_node->addChild(lbl_name);

    _hero_name = Label::create(_game_data["player_name"].string_value(), defaultFont, defaultFontSize);
    _hero_name->setPosition(0,40);
    ui_node->addChild(_hero_name);

    auto lbl_level = Label::create("Level:", defaultFont, defaultFontSize);
    lbl_level->setPosition(lbl_offset, 0);
    ui_node->addChild(lbl_level);

    std::string str_level = to_str(_game_data["level"].int_value());
    _hero_level = Label::create(str_level, defaultFont, defaultFontSize);
    _hero_level->setPosition(0,0);
    ui_node->addChild(_hero_level);

    auto lbl_gold = Label::create("Gold:", defaultFont, defaultFontSize);
    lbl_gold->setPosition(lbl_offset, -40);
    ui_node->addChild(lbl_gold);

    std::string str_gold = to_str(_game_data["gold"].int_value());
    _hero_gold = Label::create(str_gold, defaultFont, defaultFontSize);
    _hero_gold->setPosition(0,-40);
    ui_node->addChild(_hero_gold);


    Menu* menu = Menu::create(
            MenuItemFont::create("Save", CC_CALLBACK_1(SaveGameScene::onSave, this)),
            MenuItemFont::create("Load", CC_CALLBACK_1(SaveGameScene::onLoad, this)),
            MenuItemFont::create("Manage", CC_CALLBACK_1(SaveGameScene::onManage, this)),
            MenuItemFont::create("List Saves", CC_CALLBACK_1(SaveGameScene::onList, this)),
            MenuItemFont::create("Delete Save", CC_CALLBACK_1(SaveGameScene::onDelete, this)),
            MenuItemFont::create("Add Gold", CC_CALLBACK_1(SaveGameScene::onAddCoin, this)),
            nullptr
    );

    menu->alignItemsVerticallyWithPadding(5);
    menu->setPosition(size.width -220, size.height/2);
    addChild(menu);

    _ws = new network::WebSocket();
    _ws->init(*this, "ws://echo.websocket.org");
    
    return true;
}

void SaveGameScene::onPrevScene(cocos2d::Ref *sender)
{
    // Player Stats
//    Director::replaceScene();
}

void SaveGameScene::onNextScene(cocos2d::Ref *sender)
{
    // Leaderboards
    Director::getInstance()->replaceScene(LeaderboardScene::createScene());
}

void SaveGameScene::onSave(cocos2d::Ref *sender)
{
    createSave(SAVE_GAME_NAME, SAVE_GAME_DESC, _game_data.dump(), gpg::SnapshotConflictPolicy::MOST_RECENTLY_MODIFIED);
}

void SaveGameScene::onLoad(cocos2d::Ref *sender)
{
    loadSave(SAVE_GAME_NAME);
}

void SaveGameScene::onAddCoin(cocos2d::Ref *sender)
{
    _game_data["gold"] = _game_data["gold"].int_value() + 1;
    updateStats();
}

void SaveGameScene::onManage(cocos2d::Ref *sender)
{
    if ( _game_services ) {
        _game_services->Snapshots().ShowSelectUIOperation( true, true, MAX_SAVES, "Saved Games",
                [this](gpg::SnapshotManager::SnapshotSelectUIResponse const & response) {

                    if (IsSuccess(response.status)) {
                        if (response.data.Valid()) {
                            // load a game.
                            // SnapshotMetadata
                            gpg::SnapshotMetadata snapshot = response.data;
                            std::string filename = snapshot.FileName();
                            CCLOGINFO("Load game: %s with description: %s", filename.c_str(), snapshot.Description().c_str());
                            loadSave(filename);

                        } else {
                            // create game
                            createSave(SAVE_GAME_NAME, SAVE_GAME_DESC, _game_data.dump(), gpg::SnapshotConflictPolicy::MOST_RECENTLY_MODIFIED);
                        }
                    } else {
                        // error receiving info
                        CCLOGINFO("Error in snapshot select ui: %d", (int)response.status);
                    }
                });

    }
}

void SaveGameScene::onList(cocos2d::Ref *sender)
{
    if ( _game_services ) {

        _game_services->Snapshots().FetchAll(
                gpg::DataSource::CACHE_OR_NETWORK,
                [this]( const gpg::SnapshotManager::FetchAllResponse& response ) {

                    if ( IsSuccess(response.status) ) {

                        _txtStat->setString("Check log output");

                        CCLOG("Loaded %lu snapshots metadata.", response.data.size());
                        for( auto snapshotmetadata : response.data ) {
                            CCLOG("  %s: %s.", snapshotmetadata.FileName().c_str(), snapshotmetadata.Description().c_str() );
                        }
                    } else {
                        _txtStat->setString("Error loading snapshots ");
                    }
                });
    }
}

void SaveGameScene::onDelete(Ref *sender) {

    if ( _game_services ) {

        gpg::SnapshotConflictPolicy conflict_policy = gpg::SnapshotConflictPolicy::HIGHEST_PROGRESS;

        _game_services->Snapshots().Open(
                SAVE_GAME_NAME,
                conflict_policy,
                [this](gpg::SnapshotManager::OpenResponse const &response) {

                    if (IsSuccess(response.status)) {
                        _game_services->Snapshots().Delete( response.data );
                        _txtStat->setString("Save deleted");
                    } else {
                        _txtStat->setString( "Error deleting save");
                        CCLOG("Delete error, code: %d", (int)response.status);
                    }
                });
    }

}

void SaveGameScene::createSave(const std::string& filename, const std::string& description, const std::string& content, gpg::SnapshotConflictPolicy conflict_policy)
{
    if ( _game_services )
    {
        std::vector<uint8_t> data = str_to_vector(content);

        _game_services->Snapshots().Open(
                filename,
                conflict_policy,
                [this, filename, description, data](gpg::SnapshotManager::OpenResponse const &response) {

                    if (IsSuccess(response.status)) {

                        gpg::SnapshotMetadata metadata = response.data;

                        gpg::SnapshotMetadataChange::Builder builder;
                        gpg::SnapshotMetadataChange metadata_change = builder.SetDescription(description).Create();

                        _game_services->Snapshots().Commit( metadata, metadata_change, data,
                                [this, filename]( const gpg::SnapshotManager::CommitResponse &commit_response ) {
                                    _txtStat->setString( std::string("Create game ") + filename + " success." );
                                });

                    } else {
                        _txtStat->setString("Error creating game save");
                    }
                });

    }
}

/**
 * Load a game contents and print it as string on the console.
 * Scripting js/lua, expect to save games as strings (preferably serialized json objects), but native can do any binary payload.
 */
void SaveGameScene::loadSave(const std::string &filename) {
    if ( _game_services ) {
        _game_services->Snapshots().Open(
                gpg::DataSource::CACHE_OR_NETWORK,
                filename,
                gpg::SnapshotConflictPolicy::MOST_RECENTLY_MODIFIED,
                [this](gpg::SnapshotManager::OpenResponse const & response) {
                    gpg::SnapshotManager::ReadResponse responseRead = _game_services->Snapshots().ReadBlocking(response.data);

                    if ( responseRead.status == gpg::ResponseStatus::VALID ) {
                        std::string gamecontents = vec_to_string(responseRead.data);

                        _game_data = Json::parse(gamecontents);

                        updateStats();

                        _txtStat->setString( "Game Loaded" );
                    } else {
                        _txtStat->setString("Error loading game contents.");
                    }

                });
    }

}

void SaveGameScene::updateStats()
{
    _hero_name->setString(_game_data["player_name"].string_value());
    _hero_gold->setString(to_str(_game_data["gold"].int_value()));
    _hero_level->setString(to_str(_game_data["level"].int_value()));
}

// ws
void SaveGameScene::onOpen(network::WebSocket* ws)
{
    CCLOG("%s", __FUNCTION__);
    _ws->send("Hello WebSocket, I'm a text message.");
}
void SaveGameScene::onMessage(network::WebSocket* ws, const network::WebSocket::Data& data)
{
    CCLOG("%s: %s", __FUNCTION__, data.bytes);
}
void SaveGameScene::onClose(network::WebSocket* ws)
{
    CCLOG("%s", __FUNCTION__);
}
void SaveGameScene::onError(network::WebSocket* ws, const network::WebSocket::ErrorCode& error)
{
    CCLOG("%s", __FUNCTION__);
}
