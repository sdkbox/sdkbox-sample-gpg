var LayerEvents = cc.Layer.extend({

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

            new cc.MenuItemFont("FetchAll", function() {

                _context.gameServices().Events.FetchAll(
                    /**
                     *
                     * @param result {EventsFetchAllCallbackParams}
                     */
                    function(result) {
                        if (gpg.IsSuccess(result.result)) {

                            Object.keys(result.data).forEach(
                                function(key) {
                                    /**
                                     *
                                     * @param e {gpg.Event}
                                     */
                                    var e = result.data[key];
                                    __log(
                                        "Event: '" + e.name + "'" +
                                        " count:" + e.count +
                                        " visibility: " + e.visibility);
                                }
                            );
                            me._text.setString("Events fetch all got: " + Object.keys(result.data).length + "elements.");
                        } else {
                            me._text.setString("Events fetch all error: " + result.result);
                        }
                    });
            }),

            new cc.MenuItemFont("Fetch", function() {

                _context.gameServices().Events.Fetch({
                        event_id: 'CgkI6KjppNEWEAIQDA'
                    },
                    /**
                     *
                     * @param result {EventsFetchCallbackParams}
                     */
                    function(result) {
                        if (gpg.IsSuccess(result.result)) {

                            var e = result.event;
                            me._text.setString("Event: " + e.name +
                                " count:" + e.count +
                                " visibility: " + e.visibility);
                        } else {
                            me._text.setString("Events fetch error: " + result.result);
                        }
                    });
            }),

            new cc.MenuItemFont("Increment", function() {

                // there's no callback for this method.
                _context.gameServices().Events.Increment({
                    event_id: 'CgkI6KjppNEWEAIQDA',
                    increment: 2
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

var S_Events = cc.Scene.extend({
    onEnter: function() {
        this._super();
        this.addChild(new LayerEvents());
    }
});
