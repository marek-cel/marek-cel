#include <iostream>

#define BOOST_LOG_DYN_LINK 1

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

void init()
{
    boost::log::add_file_log(
        boost::log::keywords::file_name = "sample.log",
        boost::log::keywords::target_file_name = "sample.log",
        boost::log::keywords::format = "[%TimeStamp%]: %Message%"
    );

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

    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;

    return 0;
}