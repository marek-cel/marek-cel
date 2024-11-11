#include <iostream>
#include <ctime>

#include <boost/locale.hpp>

int main()
{
    boost::locale::generator gen;
    // Specify location of dictionaries
    gen.add_messages_path("../locales");
    gen.add_messages_domain("hello");
    // Generate locales and imbue them to iostream
    std::locale::global(gen(""));
    std::cout.imbue(std::locale());

    std::cout << "The language code is " << std::use_facet<boost::locale::info>(std::locale()).language() << std::endl;

    std::cout << boost::locale::format("Today {1,date} at {1,time} we had run our first localization example") % time(0) << std::endl;

    std::cout << "This is how we show numbers in this locale "  << boost::locale::as::number   << 103.34 << std::endl;
    std::cout << "This is how we show currency in this locale " << boost::locale::as::currency << 103.34 << std::endl;

    std::cout << "This is typical date in the locale " << boost::locale::as::date << std::time(0) << std::endl;
    std::cout << "This is typical time in the locale " << boost::locale::as::time << std::time(0) << std::endl;

    std::cout << "This is upper case " << boost::locale::to_upper("Hello World!")  << std::endl;
    std::cout << "This is lower case " << boost::locale::to_lower("Hello World!")  << std::endl;
    std::cout << "This is title case " << boost::locale::to_title("Hello World!")  << std::endl;
    std::cout << "This is fold case "  << boost::locale::fold_case("Hello World!") << std::endl;

    // Display a message using current system locale
    std::cout << boost::locale::translate("Hello World!") << std::endl;
}