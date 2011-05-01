#define KIWI_TESTING

#include "kiwi/core/PortSystem.hpp"
#include "kiwi/core/Container.hpp"
#include "kiwi/utils/DebugStream.hpp"
#include <assert.h>
#include "kiwi/utils/Testing.hpp"

using kiwi::out;
using kiwi::endl;

int main(){
  SCOPEDBLOCK_MACRO("core::Port::Test")

  kiwi::core::StaticDataPort<int,kiwi::core::READ_WRITE> dp;
 
  kiwi::core::StaticAccessPort<
    int
    ,kiwi::core::AlwaysCompatiblePolicy
    ,kiwi::core::READ_WRITE
  > ap;

  
  kiwi_test( "The AccessPort should not be connected at this stage.","c.ps.01a",
    ! ap.isConnected()  );
  kiwi_test( "The DataPort should not be connected at this stage.","c.ps.01b",
    ! dp.isConnected()  );

  
  kiwi_test( "Connecting ([data R+W]>>[access R+W]) should work fine.","c.ps.02",
    ap.connect( dp ) );

  out << "ap.flag: " << ap.flag() << endl; 
  out << "dp.flag: " << dp.flag() << endl; 


  kiwi_test( "The AccessPort should be connected.","c.ps.03",
    ap.isConnected() );
  kiwi_test( "The DataPort should be connected.","c.ps.03",
    dp.isConnected() );

  // check the link
  kiwi_test( "Checking the AccessPort's connectedPort() pointer.","c.ps.04",
    ap.connectedPort() == &dp );

  // disconnecting from the access port
  ap.disconnect();
  
  assert( ! ap.isConnected() );
  assert( ! dp.isConnected() );

  //connecting should be fine again
  assert( ap.connect( dp ) );
  out.foo();
  // disconnecting from the data port
  dp.disconnect();
  out.bar();
  assert( ! ap.isConnected() );
  assert( ! dp.isConnected() );


  return kiwi::utils::TestManager::getInstance()->testResult();
}
