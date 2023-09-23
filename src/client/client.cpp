#include "game.h"

int main() {
    Game app;
    
    try {
        app.preinit();
    } catch(...) {

    }

    try {
        app.init();
    } catch(...) {

    }

    try {
        app.load();
    } catch(...) {

    }

    try {
        app.run();
    } catch(...) {

    }

    try {
        app.unload();
    } catch(...) {

    }

    try {
        app.cleanup();
    } catch(...) {

    }

    return 0; 
}