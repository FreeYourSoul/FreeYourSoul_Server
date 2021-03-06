#include <spdlog/spdlog.h>
#include "spdlog/sinks/basic_file_sink.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <Gateway.hh>
#include <memory>
#include <Babble.hh>
#include <Authenticator.hh>


static const std::string welcomeMsg =
        "\n\n"
        "              . .    .. ............,.,...,.,..,...,..........  .                         \n"
        "                     ......... ......,...,,,,,.,,,,,,,,,,,,...,..........  .  .                    \n"
        "                  .. .... ..........,..,,,,,,,,,,,,***,,,,,,,,,,..........   .                     \n"
        "                   . ................,,,,,,,*****////////**,,,,,.,.......... . .                   \n"
        "               ..  ......,......,.,,,,*,*****//((&@@&((//****,,,,,,,............                   \n"
        "               ........,.......,,,,,,,*****/%@@@@#((((///******,*,,..,,............ .  .           \n"
        "                 . .........,,,,,,,,******/@@@@@@@&%(((/////******,,,,.,,.......,...               \n"
        "                . ........,.,,,,*********///((#&@@@@@@@@(///*****,,,,......... . .. .            \n"
        "          .  .............,,,,,,,,,****////(((#%@@@@@@@@@@@@///****,,*,,............ . .           \n"
        "         . . ..........,,,,,,,,,,,****///((#@@@@@@@@@@@(((////***,,,,,,..,......... .            \n"
        "            ..........,,,,,,,,,,,****//((#@@@@@@@@@@@###((((////******,,*,,,,......... .           \n"
        "       .   . .. ......,.,,,,,,,*****//(((#%@@@@@@@@@@@@#((((///*****,,*,,,.....,....  .          \n"
        "       . .. .. ......,.,,,,,,*****///((#@@@@@@@@@@@@@@@@@@@#(((////***,,,,,,,.,,....   . .         \n"
        "     .   . .. . ....,.,,,,,,******//(#@@@@@@@@@@@@@@@@@@@@@@@#((///****,,,,,,,,......... .         \n"
        "          ............,,,,,******//(#@@@@@@@@@@@@@@@@@@@@@@@@@%((//*****,,,,,...,....  .           \n"
        "         . .. .........,,,,*****//(#@@@@@@@@@@@@@@@@@@@@@@@@@@@%(//*****,,,,,,.......              \n"
        "      .  . ...........,,,,,,****/((@@@@@@@@@@@@@@@@@@@@@@@@@@@@@(//*****,,,,.,...... ..            \n"
        "        . . ...........,,,,,,***/(#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@(//****,,,,,,.......               \n"
        "     . ..  ...........,,,,,,,***//(@@@@@@@@@@@@@@@@@@@@@@@@@@@@@(//*****,,,.,..... ..              \n"
        "          .. .........,.,,,,,***//(&@@@@@@@@@@@@@@@@@@@@@@@@@@@%(//*****,,,,,..........            \n"
        "             . ........,,,,,,****//(&@@@@@@@@@@@@@@@@@@@@@@@@@&(//****,,,,...........              \n"
        "              ...........,,,,,****//(@@@@@@@@@@@@@@@@@@@@@@@@%///****,,,,,,........                \n"
        "            .. ...........,,,,,****///#@@@@@@@@@@@@@@@@@@@@&(//*****,,,,,........                  \n"
        "              .. ..........,,,,,,****//((&@@@@@@@@@@@@@@@#(//*****,,,,.......... .                 \n"
        "            .  ............,,,,,,,,*****///(#&@@@@@@&%(////*****,,,,,,,........ .                  \n"
        "                . ........,.,,,,,,,,,*******//////////*******,,,,,,,,,,..........                  \n"
        "                      .......,,,,,,,,,,,,,,*************,,,,,,,,,,,.......... .  .                 \n\n"
        "oooooooooooo                             .oooooo.                  .                                                    \n"
        "`888'     `8                            d8P'  `Y8b               .o8                                                    \n"
        " 888         oooo    ooo  .oooo.o      888            .oooo.   .o888oo  .ooooo.  oooo oooo    ooo  .oooo.   oooo    ooo \n"
        " 888oooo8     `88.  .8'  d88(  \"8      888           `P  )88b    888   d88' `88b  `88. `88.  .8'  `P  )88b   `88.  .8'  \n"
        " 888    \"      `88..8'   `\"Y88b.       888     ooooo  .oP\"888    888   888ooo888   `88..]88..8'    .oP\"888    `88..8'   \n"
        " 888            `888'    o.  )88b      `88.    .88'  d8(  888    888 . 888    .o    `888'`888'    d8(  888     `888'    \n"
        "o888o            .8'     8\"\"888P'       `Y8bood8P'   `Y888\"\"8o   \"888\" `Y8bod8P'     `8'  `8'     `Y888\"\"8o     .8'     \n"
        "             .o..P'                                                                                         .o..P'      \n"
        "             `Y8P'                                                                                          `Y8P'       \n"
        "                                                                                                                        \n\n\n";

void welcome(bool verbose) {
    auto my_logger = spdlog::stdout_color_mt("c");
    std::cout << "okok1" << std::endl;
#ifdef DEBUG_LEVEL
    sys_logger->set_level(spdlog::level::debug);
#else
    my_logger->set_level(spdlog::level::debug);
#endif
    spdlog::set_pattern("[%x %H:%M:%S] [%t] [%l] %v");
    my_logger->info("Logger set to level {}\n>> log formatting>> [time] [thread] [logLevel] message logged", spdlog::get("c")->level());
    spdlog::get("c")->info(welcomeMsg);
}

int main(int argc, const char * const *argv) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    auto MyLogHandler = [] (google::protobuf::LogLevel level, const char* filename, int line, const std::string& message) {
        spdlog::get("c")->debug("PROTOBUF log handler : file {}, line {}, msg {}", filename, line, message);
    };
    google::protobuf::SetLogHandler(MyLogHandler);

    fys::gateway::Context ctx(argc, argv);
    welcome(ctx.isVerbose());
    ctx.logContext();
    fys::gateway::Gateway::start(ctx);
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
