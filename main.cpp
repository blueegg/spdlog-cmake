#include <string>
#include <vector>
#include <fstream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "fmt/format.h"
#include "fmt/chrono.h"
#include "fmt/ranges.h"
#include "fmt/os.h"

#include <cpr/cpr.h>

void test_cpr()
{
    cpr::Response r = cpr::Get(cpr::Url{"https://api.github.com/repos/whoshuu/cpr/contributors"},
                      cpr::Authentication{"user", "pass"},
                      cpr::Parameters{{"anon", "true"}, {"key", "value"}});
                      
    fmt::print("status:{}, text= {}", r.status_code, r.text);

    r = cpr::Get(cpr::Url{"https://quanthub.baiwenbao.com/"});
    fmt::print("status:{}, text= {}", r.status_code, r.text);

}

#include "httplib.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

void test_httplib()
{
    std::string host = "https://quanthub.baiwenbao.com";
    const std::string client = "bwb_guangjin";

    httplib::Client cli(host.c_str());

    if (auto res = cli.Get("/")){
        std::cout << res->status << std::endl;
        std::cout << res->body << std::endl;
    } else
    {
        std::cout << "error code: " << res.error() << std::endl;
    }

    // Get Token    
    const std::string username = "kewen";
    const std::string password = "Santa97613303";

    httplib::Params header {
        {"username", username},
        {"password", password}
    };

    // Authentication
    if (auto res = cli.Post("/token", header)) {
        std::cout << res->status << std::endl;
        std::cout << res->body << std::endl;

        auto j = json::parse(res->body);
        cli.set_bearer_token_auth(j["access_token"].get<std::string>().c_str());
    }
    else {
        std::cout << "error get token" << std::endl;
    }

    if (auto res = cli.Get("/v1/latest/bwb_guangjin")) {
        std::cout << res->status << std::endl;
        std::cout << res->body << std::endl;
    }

    // post positions
    json jsonPositions = json::array();
    json pos = {
            {"BuySellType", 1},
            {"InstrumentID", "Ap110"},
            {"Margin", 20000},
            {"OpenAvgPrice", 223.4},
            {"TodayAmount", 0},
            {"YesterdayAmount", 1}
    };
    jsonPositions.push_back(pos);

    std::cout << jsonPositions.dump() << std::endl;

    if (auto res = cli.Post("/v1/positions/bwb_guangjin", jsonPositions.dump(), "application/json")){
       std::cout << res->status << std::endl; 
    }

}

int main() {

    spdlog::info("Sample Info output.");
    spdlog::warn("Sample Warn output.");
    spdlog::error("Sample Error output.");

    auto filelog = spdlog::basic_logger_mt("sample-logger", "sample-log.txt");

    filelog.get()->info("Sample Info output.");
    filelog.get()->warn("Sample Warn output.");
    filelog.get()->error("Sample Error output.");

    std::string s = fmt::format("I'd rather be {1} than {0}.", "right", "happy");

    fmt::print("Hello world\n");

    using namespace std::literals::chrono_literals;
    fmt::print("Default format: {} {}\n", 42s, 100ms);
    fmt::print("strftime-like format: {:%H:%M:%S}\n", 3h + 15min + 30s);
    std::vector<int> v = {1, 2, 3};
    fmt::print("{}\n", v);

    auto out = fmt::output_file("guide.txt");
    out.print("Don't {}\n", "Panic");
    
    test_cpr();
    test_httplib();
    return 0;
}
