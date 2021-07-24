pkg load control
s = tf('s');
source( 'include_sys_tf_lead_lag.m' );
bode(g);

source( 'include_sys_plot_bode.m' );

print( gcf, '../sys_bode_lead_lag.png', '-dpng', '-r150' );
