#include "src/lockstep/Server.h"
#include "src/base/NetworkManager.h"
#include "src/base/Connection.h"
#include "src/base/Timer.h"
#include "src/lockstep/Room.h"

int main()
{
  Server server("127.0.0.1",7777);
  server.run();

  return 0;
}