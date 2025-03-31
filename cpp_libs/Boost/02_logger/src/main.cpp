#include <iostream>

#define BOOST_LOG_DYN_LINK 1

#include <boost/log/core.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

void init()
{
    boost::log::add_file_log(
        boost::log::keywords::file_name = "sample.log",
        boost::log::keywords::target_file_name = "sample.log",
        boost::log::keywords::auto_flush = true,
        boost::log::keywords::format = "[%TimeStamp%] %Message%"
    );

    boost::log::add_common_attributes();

    //boost::log::add_file_log( "sample.log" );

    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::info
    );
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;

    init();
    BOOST_LOG_TRIVIAL(error) << "Hello, world!";


    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;

    return 0;
}