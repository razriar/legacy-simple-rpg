#include <cstdlib>
#include <iostream>
#include <memory>
#include <pqxx/pqxx>

#include "bll/metadata.h"
#include "bll/registry.h"
#include "bll/userservice.h"
#include "dal/dbcontext.h"
#include "dtl/actions/echoaction.h"
#include "dtl/actions/signinaction.h"
#include "dtl/actions/signupaction.h"
#include "dtl/frontcontroller.h"
#include "dtl/serverfactory.h"

class DBValue {
   private:
    std::string value_;

   public:
    DBValue(std::string value) : value_(value) {}
};
int main() {
    bll::InitMetadata();
    auto service = std::make_shared<bll::UserService<dal::DBContext>>();
    bll::Registry::SetUserService(service);
    auto controller = dtl::FrontController();
    controller.RegisterAction<dtl::EchoAction>();
    controller.RegisterAction<dtl::SignUpAction>();
    controller.RegisterAction<dtl::SignInAction>();
    auto factory = dtl::ServerFactory();
    auto server = factory.Create<dtl::Server>(controller, "8000", "4");
    server.Run();
    return EXIT_SUCCESS;
}
