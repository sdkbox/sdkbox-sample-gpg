var LayerSnapShot = cc.Layer.extend({

    _text: null,

    ctor: function() {
        //////////////////////////////
        // 1. super init first
        this._super();

        this.__createMenu();

        this._text = new cc.LabelTTF("", "sans", 24);
        this._text.x = cc.Director.getInstance().getWinSize().width / 2;
        this._text.y = 120;
        this.addChild(this._text);
    },

    __createMenu: function() {

        var me = this;

        cc.MenuItemFont.setFontName("sans");
        var size = cc.Director.getInstance().getWinSize();

        var menu = new cc.Menu(
            new cc.MenuItemFont("Show SnapshotUI", function() {
                if (_context.isSignedIn()) {
                    _context.gameServices().Snapshots.ShowSelectUIOperation({
                            allow_create: true,
                            allow_delete: true,
                            max_snapshots: 8,
                            title: 'a title for snapshoting'
                        },
                        /**
                         *
                         * @param result {tSnapshotShowSelectionUIOperationCallbackResult}
                         */
                        function(result) {
                            if (result.result === 'load') {

                                __log('snapshot load game');
                                var metadata = result.metadata;

                                _context.gameServices().Snapshots.Load({
                                        conflict_policy: gpg.SnapshotConflictPolicy.DefaultConflictPolicy,
                                        filename: metadata.filename
                                    },
                                    /**
                                     *
                                     * @param result {tSnapshotLoadCallbackResult}
                                     */
                                    function(result) {
                                        var metadata = JSON.stringify(result.metadata);
                                        __log(' load game. metadata: ' + metadata);
                                        if (gpg.IsSuccess(result.result)) {
                                            me._text.setString('load game metadata ok: ' + metadata);
                                        } else {
                                            me._text.setString(' result not valid, so no contents.');
                                        }
                                    }
                                );

                            } else if (result.result === 'create') {

                                __log('snapshot create game');

                                _context.gameServices().Snapshots.Save({
                                        filename: 'gpg_testing',
                                        description: 'a valued saved game',
                                        data: JSON.stringify({
                                            a: 7,
                                            b: 'abcd',
                                            c: {
                                                d: false,
                                                e: [1, 2, 3],
                                                f: Math.random()
                                            }
                                        })
                                    },
                                    function(result) {
                                        __log(' saved game. metadata: ' + JSON.stringify(result.metadata));
                                        if (gpg.IsSuccess(result.result)) {
                                            me._text.setString('saved ok');
                                        } else {
                                            me._text.setString('  saved with error. code: ' + result.result);
                                        }
                                    }
                                );

                            } else if (result.result === 'error') {
                                me._text.setString('snapshot ui error: ' + result.error_code);
                            } else {
                                me._text.setString('snapshot ui error, unknown result ');
                            }
                        }
                    );
                }
            }),
            new cc.MenuItemFont("Fetch all games", function() {

                _context.gameServices().Snapshots.FetchAll({
                        data_source: gpg.DataSource.CACHE_OR_NETWORK
                    },
                    function(result) {
                        if (gpg.IsSuccess(result.result)) {
                            me._text.setString('Fetch all games success. Snapshots loaded: ' + result.metadata_array.length);

                            result.metadata_array.forEach(
                                /**
                                 *
                                 * @param metadata {gpg.SnapshotMetadata}
                                 */
                                function(metadata) {
                                    __log('       ' + metadata.filename);
                                });

                        } else {
                            me._text.setString('Fetch all games error. Code: ' + result.result);
                        }
                    }
                )
            }),
            new cc.MenuItemFont("Delete gpg_testing game", function() {

                var filename = 'gpg_testing';

                _context.gameServices().Snapshots.Delete(filename, function(result) {
                    if (result.result === 'success') {
                        me._text.setString('game ' + filename + ' deleted.');
                    } else {
                        me._text.setString('game ' + filename + ' did not delete. Reason:' + result.error_code + '.');
                    }
                });
            }),

            new cc.MenuItemFont("Main menu", function() {
                cc.director.runScene(new HelloWorldScene());
            })
        );

        menu.alignItemsVerticallyWithPadding(3);
        menu.x = size.width / 2;
        menu.y = size.height / 2 + 40;
        this.addChild(menu);
    }
});

var S_SnapShots = cc.Scene.extend({
    onEnter: function() {
        this._super();
        var l = new LayerSnapShot();
        this.addChild(l);
    }
});
