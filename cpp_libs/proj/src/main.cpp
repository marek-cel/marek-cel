#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>

#include <proj.h>

#include <proj/coordinateoperation.hpp>
#include <proj/crs.hpp>
#include <proj/io.hpp>
#include <proj/util.hpp>

#include <units.h>

using namespace std;

using namespace NS_PROJ::crs;
using namespace NS_PROJ::io;
using namespace NS_PROJ::operation;
using namespace NS_PROJ::util;

using namespace units::literals;

struct Point
{
    units::length::meter_t x = 0.0_m;
    units::length::meter_t y = 0.0_m;
};

struct LatLon
{
    units::angle::degree_t lat = 0.0_deg;
    units::angle::degree_t lon = 0.0_deg;
};

Point ConvertLatLonToMercator(const LatLon &latlon)
{
    Point result;

    // Initialize PROJ context
    PJ_CONTEXT *ctx = proj_context_create();
    if (!ctx) {
        std::cerr << "Failed to create PROJ context." << std::endl;
        throw std::runtime_error("Failed to create PROJ context.");
    }

    // Define transformation from WGS84 geodetic coordinates to Mercator projection
    PJ *mercator = proj_create_crs_to_crs(ctx, "EPSG:4326", "EPSG:3857", nullptr);
    if (!mercator) {
        std::cerr << "Failed to create Mercator transformation." << std::endl;
        proj_context_destroy(ctx);
        throw std::runtime_error("Failed to create Mercator transformation.");
    }

    PJ *mercator_trans = proj_normalize_for_visualization(ctx, mercator);
    proj_destroy(mercator);
    if (!mercator_trans) {
        std::cerr << "Failed to normalize transformation." << std::endl;
        proj_context_destroy(ctx);
        throw std::runtime_error("Failed to normalize transformation.");
    }

    // Transform coordinates
    PJ_COORD input = proj_coord(latlon.lon(), latlon.lat(), 0, 0);
    PJ_COORD output = proj_trans(mercator_trans, PJ_FWD, input);

    // Output Mercator coordinates


    result.x = output.xy.x * 1.0_m;
    result.y = output.xy.y * 1.0_m;

    // Cleanup
    proj_destroy(mercator_trans);
    proj_context_destroy(ctx);

    return result;
}

void ProjC_API()
{
    PJ_CONTEXT *C;
    PJ *P;
    PJ *norm;
    PJ_COORD a, b;

    /* or you may set C=PJ_DEFAULT_CTX if you are sure you will     */
    /* use PJ objects from only one thread                          */
    C = proj_context_create();

    P = proj_create_crs_to_crs(
        C, "EPSG:4326", "+proj=utm +zone=32 +datum=WGS84", /* or EPSG:32632 */
        NULL);

    if (0 == P) {
        fprintf(stderr, "Failed to create transformation object.\n");
        return;
    }

    /* This will ensure that the order of coordinates for the input CRS */
    /* will be longitude, latitude, whereas EPSG:4326 mandates latitude, */
    /* longitude */
    norm = proj_normalize_for_visualization(C, P);
    if (0 == norm) {
        fprintf(stderr, "Failed to normalize transformation object.\n");
        return;
    }
    proj_destroy(P);
    P = norm;

    /* a coordinate union representing Copenhagen: 55d N, 12d E */
    /* Given that we have used proj_normalize_for_visualization(), the order */
    /* of coordinates is longitude, latitude, and values are expressed in */
    /* degrees. */
    a = proj_coord(12, 55, 0, 0);

    /* transform to UTM zone 32, then back to geographical */
    b = proj_trans(P, PJ_FWD, a);
    printf("easting: %.3f, northing: %.3f\n", b.enu.e, b.enu.n);

    b = proj_trans(P, PJ_INV, b);
    printf("longitude: %g, latitude: %g\n", b.lp.lam, b.lp.phi);

    /* Clean up */
    proj_destroy(P);
    proj_context_destroy(C); /* may be omitted in the single threaded case */
}

void ProjCpp_API()
{
    // We start by creating a database context (osgeo::proj::io::DatabaseContext)
    // with the default settings to find the PROJ database.
    osgeo::proj::io::DatabaseContextNNPtr
    //auto
    dbContext =
        osgeo::proj::io::DatabaseContext::create();

    // We then instantiate a generic authority factory (osgeo::proj::io::AuthorityFactory),
    // that is not tied to a particular authority, to be able to get transformations
    // registered by different authorities. This can only be used for
    // a osgeo::proj::operation::CoordinateOperationContext, and not to instantiate
    // objects of the database which are all tied to a non-generic authority.
    osgeo::proj::io::AuthorityFactoryPtr
    //auto
    authFactory =
        osgeo::proj::io::AuthorityFactory::create(dbContext, std::string());

    // We create a coordinate operation context, that can be customized to amend
    // the way coordinate operations are computed. Here we ask for default settings,
    // as we have a coordinate operation that just involves a "simple" map projection
    // in the same datum.
    auto coord_op_ctxt =
        osgeo::proj::operation::CoordinateOperationContext::create(authFactory, nullptr, 0.0);

    // We instantiate a authority factory for EPSG related objects.
    auto authFactoryEPSG = osgeo::proj::io::AuthorityFactory::create(dbContext, "EPSG");

    // We instantiate the source CRS from its code: 4326, for WGS 84 latitude/longitude.
    auto sourceCRS = authFactoryEPSG->createCoordinateReferenceSystem("4326");

    // We instantiate the source CRS from its PROJ.4 string (it would be possible
    // to instantiate it from its 32631 code, similarly to above), and cast
    // the generic osgeo::proj::util::BaseObject to the osgeo::proj::crs::CRS class
    // required later.
    auto targetCRS =
        NN_CHECK_THROW(osgeo::proj::util::nn_dynamic_pointer_cast<CRS>(osgeo::proj::io::createFromUserInput(
            "+proj=utm +zone=31 +datum=WGS84 +type=crs", dbContext)));

    // WARNING!
    // The use of PROJ strings to describe a CRS is not recommended. One of
    // the main weaknesses of PROJ strings is their inability to describe
    // a geodetic datum, other than the few ones hardcoded in the +datum parameter.

    // We ask for the list of operations available to transform from the source
    // to the target CRS with the osgeo::proj::operation::CoordinateOperationFactory::createOperations()
    // method.
    auto list = osgeo::proj::operation::CoordinateOperationFactory::create()->createOperations(
        sourceCRS, targetCRS, coord_op_ctxt);

    // We check that we got a non-empty list of operations. The list is sorted from
    // the most relevant to the less relevant one. Cf Filtering and sorting
    // of coordinate operations for more details on the sorting of those operations.
    // For a transformation between a projected CRS and its base CRS, like we do here,
    // there will be only one operation.
    assert(!list.empty());

    // We create an execution context (must only be used by one thread at a time)
    // with the proj_context_create() function.
    PJ_CONTEXT *ctx = proj_context_create();

    // We create a coordinate transformer (osgeo::proj::operation::CoordinateTransformer)
    // from the first operation of the list:
    auto transformer = list[0]->coordinateTransformer(ctx);

    // We can now transform a point with the osgeo::proj::operation::CoordinateTransformer::transform()
    // method. Note that the the expected input values should be passed in the order
    // and the unit of the successive axis of the input CRS. Similarly the values
    // returned in the v[] array of the output PJ_COORD are in the order and
    // the unit of the successive axis of the output CRS. For coordinate operations
    // involving a time-dependent operation, coord.v[3] is the decimal year of
    // the coordinate epoch of the input (or HUGE_VAL to indicate none).
    PJ_COORD c = {{
        49.0,    // latitude in degree
        2.0,     // longitude in degree
        0.0,     // z ordinate. unused
        HUGE_VAL // time ordinate. unused
    }};
    c = transformer->transform(c);

    // and output the result:
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Easting: " << c.v[0] << std::endl;  // should be 426857.988
    std::cout << "Northing: " << c.v[1] << std::endl; // should be 5427937.523

    // We need to clean up the PJ_CONTEXT handle before exiting with the proj_context_destroy() function.
    proj_context_destroy(ctx);
}

int main()
{
    std::cout << "Hello, PROJ!" << std::endl;

    ProjC_API();
    ProjCpp_API();

    LatLon input;
    Point output;

    // input.lon = 21.0122_deg;
    // input.lat = 52.2297_deg;
    // output = ConvertLatLonToMercator(input);
    // std::cout << "lon= " << input.lon << " lat= " << input.lat << " x= " << output.x << " y= " << output.y << std::endl;

    input.lon = 30.0_deg;
    input.lat = 0.0_deg;
    output = ConvertLatLonToMercator(input);
    std::cout << "lon= " << input.lon << " lat= " << input.lat << " x= " << output.x << " y= " << output.y << std::endl;

    return 0;
}
