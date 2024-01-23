/****************************************************************************//*
 * Copyright (C) 2021 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/

/**
 * Converts geodetic coordinates into cartesian coordinates.
 * @see Department of Defence World Geodetic System 1984, NIMA, TR-8350.2, 2000
 */
function geo2wgs( lat, lon, alt )
{
    var a   = 6378137.0;            // [m] equatorial radius
    var b   = 6356752.3142;         // [m] polar radius
    var a2  = a * a;                // [m^2] equatorial radius squared
    var b2  = b * b;                // [m^2] polar radius squared
    var e2  = 6.6943799901400e-3;   // [-] ellipsoid first eccentricity squared
        
    var sinLat = Math.sin( lat );
    var cosLat = Math.cos( lat );
    var sinLon = Math.sin( lon );
    var cosLon = Math.cos( lon );

    var n = a / Math.sqrt( 1.0 - e2 * sinLat*sinLat );

    var x = ( n + alt ) * cosLat * cosLon;
    var y = ( n + alt ) * cosLat * sinLon;
    var z = ( n * ( b2 / a2 ) + alt ) * sinLat;
    
    return [ x, y, z ];
}

////////////////////////////////////////////////////////////////////////////////
    
/**
 * Converts cartesian coordinates into geodetic coordinates.
 * @see Department of Defence World Geodetic System 1984, NIMA, TR-8350.2, 2000
 * @see Zhu J.: Conversion of Earth-centered Earth-fixed coordinates to geodetic coordinates, 1994
 */
function wgs2geo( x, y, z )
{
    var a   = 6378137.0;            // [m] equatorial radius
    var b   = 6356752.3142;         // [m] polar radius
    var a2  = a * a;                // [m^2] equatorial radius squared
    var b2  = b * b;                // [m^2] polar radius squared
    var e_2 = 6.6943799901400e-3;   // [-] ellipsoid first eccentricity squared
    var ep2 = 6.7394967422800e-3;   // [-] ellipsoid second eccentricity squared
    
    var z2 = z*z;
    var r  = Math.sqrt( x*x + y*y );
    var r2 = r*r;
    var e2 = a2 - b2;
    var f  = 54.0 * b2 * z2;
    var g  = r2 + ( 1.0 - e_2 )*z2 - e_2*e2;
    var c  = e_2*e_2 * f * r2 / ( g*g*g );
    var s  = Math.pow( 1.0 + c + Math.sqrt( c*c + 2.0*c ), 1.0/3.0 );
    var p0 = s + 1.0/s + 1.0;
    var p  = f / ( 3.0 * p0*p0 * g*g );
    var q  = Math.sqrt( 1.0 + 2.0*( e_2*e_2 )*p );
    var r0 = -( p * e_2 * r )/( 1.0 + q ) + Math.sqrt( 0.5*a2*( 1.0 + 1.0/q ) - p*( 1.0 - e_2 )*z2/( q + q*q ) - 0.5*p*r2 );
    var uv = r - e_2*r0;
    var u  = Math.sqrt( uv*uv + z2 );
    var v  = Math.sqrt( uv*uv + ( 1.0 - e_2 )*z2 );
    var z0 = b2 * z / ( a * v );

    var alt = u * ( 1.0 - b2 / ( a * v ) );
    var lat = Math.atan( ( z + ep2*z0 )/r );
    var lon = Math.atan2( y, x );
    
    return [ lat, lon, alt ];
}

////////////////////////////////////////////////////////////////////////////////

/** */
function deg2rad( ang )
{
    return ang * Math.PI / 180.0;
}

/** */
function rad2deg( ang )
{
    return ang * 180.0 / Math.PI;
}

////////////////////////////////////////////////////////////////////////////////

function calcGeo2XYZ()
{
    var inp_lon = parseFloat( document.getElementById( "inp_lon" ).value );
    var inp_lat = parseFloat( document.getElementById( "inp_lat" ).value );
    var inp_alt = parseFloat( document.getElementById( "inp_alt" ).value );
    
    if ( inp_lon < -180.0 || inp_lon > 180 || inp_lat < -90 || inp_lat > 90 )
    {
        document.getElementById( "calc_error" ).style.display = "block";
        
        document.getElementById( "out_x" ).innerHTML = "";
        document.getElementById( "out_y" ).innerHTML = "";
        document.getElementById( "out_z" ).innerHTML = "";
    }
    else
    {
        document.getElementById( "calc_error" ).style.display = "none";
        
        var inp_lon_rad = deg2rad( inp_lon );
        var inp_lat_rad = deg2rad( inp_lat );
        
        var result = geo2wgs( parseFloat(inp_lat_rad),
                              parseFloat(inp_lon_rad),
                              parseFloat(inp_alt) );
        
        var out_x = result[ 0 ];
        var out_y = result[ 1 ];
        var out_z = result[ 2 ];
        
        document.getElementById( "out_x" ).innerHTML = out_x.toFixed(3);
        document.getElementById( "out_y" ).innerHTML = out_y.toFixed(3);
        document.getElementById( "out_z" ).innerHTML = out_z.toFixed(3);
    }
}

////////////////////////////////////////////////////////////////////////////////

function calcXYZ2Geo()
{
    var inp_x = parseFloat( document.getElementById( "inp_x" ).value );
    var inp_y = parseFloat( document.getElementById( "inp_y" ).value );
    var inp_z = parseFloat( document.getElementById( "inp_z" ).value );
    
    var result = wgs2geo( parseFloat(inp_x),
                          parseFloat(inp_y),
                          parseFloat(inp_z) );
    
    var out_lat = rad2deg( result[ 0 ] );
    var out_lon = rad2deg( result[ 1 ] );
    var out_alt = result[ 2 ];
    
    document.getElementById( "out_lat" ).innerHTML = out_lat.toFixed(6);
    document.getElementById( "out_lon" ).innerHTML = out_lon.toFixed(6);
    document.getElementById( "out_alt" ).innerHTML = out_alt.toFixed(3);
}

////////////////////////////////////////////////////////////////////////////////

function calcAllWGS()
{
    calcGeo2XYZ();
    calcXYZ2Geo();
}
