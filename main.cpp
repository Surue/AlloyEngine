#include <application.h>

class EmptyApp : public alloy::Application {
public:
    EmptyApp(const alloy::ApplicationInitSettings& applicationInitSettings) : Application(applicationInitSettings){
        
	}

protected:
    void Init() override {}
};

int main() {
    alloy::ApplicationInitSettings engineInitSettings{
        "Alloy Engine",
        math::ivec2(600, 600)
    };
	
    EmptyApp emptyApp(engineInitSettings);

    emptyApp.Start();

    return EXIT_SUCCESS;
}
