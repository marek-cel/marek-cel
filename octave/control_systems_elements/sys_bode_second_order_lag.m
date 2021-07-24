pkg load control
s = tf('s');
source( 'include_sys_tf_second_order_lag.m' );
bode(g);

source( 'include_sys_plot_bode.m' );

print( gcf, '../sys_bode_second_order_lag.png', '-dpng', '-r150' );
