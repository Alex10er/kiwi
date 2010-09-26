
#include "core/Commons.hpp"

#include "core/Filter.hpp"

#include "generic/SimpleValue.hpp"

#include "utils/types.hpp"

#include <vector>

using namespace kiwi;
using namespace kiwi::core;

typedef kiwi::generic::ValueReader<float> FloatReader; 
typedef kiwi::generic::ValueWriter<float> FloatWriter;


// ---------------------------------------------------------------------------------------
// --------------------- A simple Filter -------------------------------------------------
// ---------------------------------------------------------------------------------------



// compute the sum of two Value<> resources and place it in an other Value<>
template<typename TValueType>
class TestFilter : public Filter
{
public:
	
// ---------------------------------------------------------------------------------------
	TestFilter() : Filter()
	{
		kiwi::string sType( kiwi::string("value_")+ types::str<TValueType>() );
		addReaderInputPort(sType, "A");
		addReaderInputPort(sType, "B");
		
		addWriterInputPort(sType, "Write Result");
		
	}
	~TestFilter() {}

// ---------------------------------------------------------------------------------------
	void process()
	{
		ScopedBlockMacro(proc_block, "TestFilter::process()");
		if(!isReady() )
		{
			debug.error() << "TestFilter::Process error : not ready" << endl();
			return;
		}

		debug.print() << "Allocate Reader #0" << endl;
		FloatReader A( readerInputPort(0) );
		
		debug.print() << "Allocate Reader #1" << endl;
		FloatReader B( readerInputPort(1) );
		
		debug.print() << "Allocate Writer #0" << endl;
		FloatWriter result( writerInputPort(0) );
		
		debug.beginBlock( "compute..");
			result.set( A.get() + A.get() );
			debug.print() << "result :" << result.get() << endl();
		debug.endBlock( "compute..");
	}
	
	
// ---------------------------------------------------------------------------------------
	bool readyCondition()
	{
		return (readerInputPort(0).isConnected()
			&& readerInputPort(1).isConnected()
			&& writerInputPort(0).isConnected() );
	}
};



// ---------------------------------------------------------------------------------------
// ---------------------------- Main -----------------------------------------------------
// ---------------------------------------------------------------------------------------




int main()
{

ScopedBlockMacro(s2, "kiwi::Test");

debug.beginBlock("int main() ");

	debug.beginBlock("Allocate the resources");
		generic::Value<float> resource1(10);
		generic::Value<float> resource2(10);
		generic::Value<float> resourceResult(42);

		TestFilter<float> myTest;
	debug.endBlock();

	debug.beginBlock("connect the ports");
		resource1.readerOutputPort(0) >> myTest.readerInputPort(0);
		resource2.readerOutputPort(0) >> myTest.readerInputPort(1);
		resourceResult.writerOutputPort(0) >> myTest.writerInputPort(0);
	debug.endBlock();

	myTest.process();
	
	
	
debug.endBlock();
	return 0;
}


