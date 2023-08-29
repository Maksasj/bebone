#ifndef _GAME_H_
#define _GAME_H_

#include "client_proxy.h"
#include "server_proxy.h"

class Game {
    private:
        std::unique_ptr<IProxy> proxy;

    public:
        Game() {
            proxy = std::make_unique<ClientProxy>();
        }

        void preinit() {
            proxy->preinit();
        }

        void init() {
            proxy->init();
        }

        void load() {
            proxy->load();
        }

        void run() {
            proxy->run();
        }

        void unload() {
            proxy->unload();
        }

        void cleanup() {
            proxy->cleanup();
        }
};

#endif
