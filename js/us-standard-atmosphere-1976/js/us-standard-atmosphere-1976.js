/****************************************************************************//*
 * Copyright (C) 2021 Marek M. Cel
 ******************************************************************************/

/**
 * Calculates atmosphere parameters.
 * @see US Standard Atmosphere 1976, NASA/NOAA, TM-X-74335
 */
function calcAtmosphere( alt )
{     
    var m = 28.964507914535;  // [kg/kmol] mean molecular weight (28.964507914535)
    
    var r     = 8.31432e3;    // [J/(kmol*K)] universal gas constant (US Standard Atmosphere 1976, Table 2, p.2)
    var s     = 110.0;        // [K] Sutherland constant             (US Standard Atmosphere 1976, Table 2, p.2)
    var beta  = 1.458e-6;     // [kg/(s*m*K^0.5)] a constant used in computing dynamic viscosity (US Standard Atmosphere 1976, Table 2, p.2)
    var gamma = 1.4;          // [-] a constant taken to represent the ratio of specific heat at constant pressure to the specific heat at constant volume (cp/cv) (US Standard Atmosphere 1976, Table 2, p.2)
    var wgs_g = 9.80665;      // [m/s^2] standard gravitional acceleration
    
    var t_0   = 288.15;       // [K]      standard sea level temperature (288.15 K or 15 deg C)
    var p_0   = 101325.0;     // [Pa]     standard sea level pressure    (1013.25 hPa)
    var rho_0 = 1.225;        // [kg/m^3] standard sea level density     (1.225 kg/m^3)
    
    var valid = false;
      
    var temp  = 1.0 / 0.0;
    var press = 1.0 / 0.0;
    var dens  = 1.0 / 0.0;
    var sound = 1.0 / 0.0;
    var visc  = 1.0 / 0.0;
    var kinViscosity = 1.0 / 0.0;
    
    if ( alt <= 84852.0 )
    {
        valid = true;
        
        var hb = 0.0;
        var pb = 0.0;
        var tb = 0.0;
        var lb = 0.0;
        
        // [m]   altitude values       (US Standard Atmosphere 1976, Table 4, p.3)
        // [Pa]  pressure values       (US Standard Atmosphere 1976, Table I, p.50-73)
        // [K]   temperature values    (US Standard Atmosphere 1976, Table I, p.50-73)
        // [K/m] temperature gradients (US Standard Atmosphere 1976, Table 4, p.3)
        if ( alt <= 11000  )
        {
            hb = 0.0;
            
            pb = 101325.0;
            
            // const rate -6.5 K/km
            tb = 288.15;
            lb = -6.5e-3;
        }
        else if ( alt > 11000 && alt <= 20000  )
        {
            hb = 11000.0;
            
            pb = 22632.0;
            
            // const
            tb = 216.65;
            lb = 0.0;
        }
        else if ( alt > 20000 && alt <= 32000  )
        {
            hb = 20000.0;
            
            pb = 5474.8;
            
            // const rate +1.0 K/km
            tb = 216.65;
            lb = 1.0e-3;
        }
        else if ( alt > 32000 && alt <= 47000  )
        {
            hb = 32000.0;
            
            pb = 868.01;
            
            // const rate +2.8 K/km
            tb = 228.65;
            lb = 2.8e-3;
        }
        else if ( alt > 47000 && alt <= 51000  )
        {
            hb = 47000.0;
            
            pb = 110.9;
            
            // const
            tb = 270.65;
            lb = 0.0;
        }
        else if ( alt > 51000 && alt <= 71000  )
        {
            hb = 51000.0;
            
            pb = 66.938;
            
            // const rate -2.8 K/km
            tb = 270.65;
            lb = -2.8e-3; 
        }
        else if ( alt > 71000 && alt <= 84852  )
        {
            hb = 71000.0;
            
            pb = 3.9564;
            
            // const rate -2.0 K/km
            tb = 214.65;
            lb = -2.0e-3;
        }
        
        var delta_h = alt - hb;

        // [K] temperature, US Standard Atmosphere 1976, p.10
        temp = tb + lb * delta_h;
        
        // [Pa] pressure, US Standard Atmosphere 1976, p.12
        if ( Math.abs( lb ) < 1.0e-6 )
        {
            press = pb * Math.exp( -( wgs_g * m * delta_h ) / ( r * tb ) );
        }
        else
        {
            press = pb * Math.pow( tb / temp, ( wgs_g * m ) / ( r * lb ) );
        }

        // [kg/m^3] density, US Standard Atmosphere 1976, p.15
        dens = ( press * m ) / ( r * temp );

        // [m/s] speed of sound, US Standard Atmosphere 1976, p.18
        sound = Math.sqrt( ( gamma * r * temp ) / m );

        // [Pa*s] dynamic viscosity, US Standard Atmosphere 1976, p.19
        visc = beta * Math.pow( temp, 3.0 / 2.0 ) / ( temp + s );

        // [m^2/s] kinematic viscosity, US Standard Atmosphere 1976, p.19
        kinViscosity = visc / dens;
    }
    
    return [ valid, temp, press, dens, sound, visc ];
}

////////////////////////////////////////////////////////////////////////////////

/** */
function k2c( temp )
{
    return ( temp - 273.15 );
}

/** */
function k2f( temp )
{
    return ( 9.0 * ( temp - 273.15 ) / 5.0 ) + 32.0;
}

/** */
function k2r( temp )
{
    return ( 9.0 * ( temp - 273.15 ) / 5.0 ) + 32.0 + 459.67;
}

////////////////////////////////////////////////////////////////////////////////

function calcAtmos()
{
    var alt_raw = parseFloat( document.getElementById( "inp_alt" ).value );
    
    var unit_alt   = document.getElementById( "unit_alt"   ).value;
    var unit_temp  = document.getElementById( "unit_temp"  ).value;
    var unit_press = document.getElementById( "unit_press" ).value;
    var unit_dens  = document.getElementById( "unit_dens"  ).value;
    var unit_sound = document.getElementById( "unit_sound" ).value;
    var unit_visc  = document.getElementById( "unit_visc"  ).value;
    
    var coef_alt   = 1.0;
    var coef_press = 1.0;
    var coef_dens  = 1.0;
    var coef_sound = 1.0;
    var coef_visc  = 1.0;
    
    var prec_temp  = 2;
    var prec_press = 1;
    var prec_dens  = 5;
    var prec_sound = 2;
    var prec_visc  = 6;
    
    switch ( unit_alt )
    {
        case '1': coef_alt = 1.0;    break;
        case '2': coef_alt = 0.3048; break;
    }
    
    var alt_m = coef_alt * alt_raw;
    
    var result = calcAtmosphere( parseFloat(alt_m) );
    
    var valid = result[ 0 ];
    var temp  = result[ 1 ];
    var press = result[ 2 ];
    var dens  = result[ 3 ];
    var sound = result[ 4 ];
    var visc  = result[ 5 ];
    
    switch ( unit_temp )
    {
        case '1': temp = temp;        break;
        case '2': temp = k2c( temp ); break;
        case '3': temp = k2r( temp ); break;    
        case '4': temp = k2f( temp ); break;
    }
    
    switch ( unit_press )
    {
        case '1': coef_press = 1.0;            prec_press = 1; break;
        case '2': coef_press = 0.01;           prec_press = 3; break;
        case '3': coef_press = 0.000295333727; prec_press = 5; break;
        case '4': coef_press = 0.000145037738; prec_press = 5; break;
    }
    
    switch ( unit_dens )
    {
        case '1': coef_dens = 1.0;  break;
    }
    
    switch ( unit_sound )
    {
        case '1': coef_sound = 1.0;         prec_sound = 2; break;
        case '2': coef_sound = 3.2808399;   prec_sound = 1; break;
        case '3': coef_sound = 3.6;         prec_sound = 1; break;
        case '4': coef_sound = 1.943844491; prec_sound = 2; break;
    }
    
    switch ( unit_visc )
    {
        case '1': coef_visc = 1.0;  break;
    }
    
    if ( valid )
    {
        document.getElementById( "calc_error" ).style.display = "none";
        
        press = coef_press * press;
        dens  = coef_dens  * dens;
        sound = coef_sound * sound;
        visc  = coef_visc  * visc;
        
        document.getElementById( "out_temp"  ).innerHTML = temp  .toFixed( prec_temp  );
        document.getElementById( "out_press" ).innerHTML = press .toFixed( prec_press );
        document.getElementById( "out_dens"  ).innerHTML = dens  .toFixed( prec_dens  );
        document.getElementById( "out_sound" ).innerHTML = sound .toFixed( prec_sound );
        document.getElementById( "out_visc"  ).innerHTML = visc  .toExponential( prec_visc );
    }
    else 
    {
        document.getElementById( "calc_error" ).style.display = "block";
        
        
        document.getElementById( "out_temp"  ).innerHTML = "";
        document.getElementById( "out_press" ).innerHTML = "";
        document.getElementById( "out_dens"  ).innerHTML = "";
        document.getElementById( "out_sound" ).innerHTML = "";
        document.getElementById( "out_visc"  ).innerHTML = "";
    }
}

////////////////////////////////////////////////////////////////////////////////

function altUnitChanged()
{
    var alt = document.getElementById( "inp_alt" ).value;
    
    var unit_alt = document.getElementById( "unit_alt" ).value;
    
    var coef_alt = 1.0;
    
    switch ( unit_alt )
    {
        case '1': coef_alt = 0.3048;       break;
        case '2': coef_alt = 1.0 / 0.3048; break;
    }
    
    alt = alt * coef_alt;
    
    document.getElementById( "inp_alt" ).value = alt.toFixed( 2 );
  
    calcAtmos();
}
