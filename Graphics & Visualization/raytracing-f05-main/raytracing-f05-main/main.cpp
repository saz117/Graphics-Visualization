#include "Main.h"

// Metode principal del programa

int main(int argc, char **argv) {


    cout << "Init..." <<endl;
    Q_INIT_RESOURCE(resources);


    //auto controller = make_shared<Controller>("://resources/dataBCN.txt", "://resources/configMappingData.txt", "://resources/configVis.txt");
    //auto controller = make_shared<Controller>("://resources/sphere.txt", "://resources/configMapping.txt", "://resources/configVis.txt");
    //auto controller = make_shared<Controller>("://resources/dadesEuropa.txt", "://resources/configMappingDataEuropa.txt", "://resources/configVisDataEuropa.txt");
    //auto controller = make_shared<Controller>("://resources/gizmos.txt", "://resources/configMapping.txt", "://resources/configVis.txt");
    //auto controller = make_shared<Controller>("://resources/triangleTest.txt", "://resources/configMapping.txt", "://resources/configVis.txt");
    //auto controller = make_shared<Controller>("://resources/cylinder.txt", "://resources/configMapping.txt", "://resources/configVis.txt");



    auto controller = make_shared<Controller>("://resources/marino.txt", "://resources/MapMarino.txt", "://resources/VisMarino.txt");

    controller->start(argc, argv);

    return(0);
}
