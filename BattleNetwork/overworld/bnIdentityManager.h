#include <string>
#include <cstdint>

namespace Overworld {
  /**
   * Identities should not be shared beyond a single server
   */
  class IdentityManager {
    public:
      IdentityManager(const std::string& host, uint16_t port);

      std::string GetIdentity();
    private:
      std::string path;
      std::string identity;
  };
}
