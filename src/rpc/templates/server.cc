// std
#include <iostream>
// seastar
#include <core/app-template.hh>
// smf
#include "log.h"
#include "rpc/rpc_server.h"
#include "rpc/rpc_server_stats_printer.h"
#include "rpc/rpc_handle_router.h"

// templates
#include "rpc/smf_gen/demo_service.smf.fb.h"

class storage_service : public smf_gen::fbs::rpc::SmurfStorage {};

namespace bpo = boost::program_options;

int main(int args, char **argv, char **env) {
  std::cerr << "About to start the app" << std::endl;
  distributed<smf::rpc_server_stats> stats;
  distributed<smf::rpc_server> rpc;
  smf::rpc_server_stats_printer stats_printer(stats);
  app_template app;
  // TODO(agallego) -
  // add options for printer frequency, etc
  app.add_options()("rpc_port", bpo::value<uint16_t>()->default_value(11225),
                    "rpc port");
  return app.run_deprecated(args, argv, [&] {
    smf::LOG_INFO("Setting up at_exit hooks");
    engine().at_exit([&] { return rpc.stop(); });
    engine().at_exit([&] { return stats.stop(); });


    auto &&config = app.configuration();
    uint16_t port = config["rpc_port"].as<uint16_t>();
    smf::LOG_INFO("starting stats");
    return stats.start()
      .then([&rpc, &stats, port] {
        return rpc.start(std::ref(stats), port)
          .then([&rpc] {
            smf::LOG_INFO("Registering smf_gen::fbs::rpc::storage_service");
            return rpc.invoke_on_all(
              &smf::rpc_server::register_service<storage_service>);
          });
      })
      .then([&rpc] {
        smf::LOG_INFO("Invoking rpc start on all cores");
        return rpc.invoke_on_all(&smf::rpc_server::start);
      });
  });
}
