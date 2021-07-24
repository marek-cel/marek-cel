pkg load control
s = tf('s');
source( 'include_sys_tf_second_order_lag.m' );
impulse(g);

source( 'include_sys_plot_impulse.m' );

print( gcf, '../sys_impulse_second_order_lag.png', '-dpng', '-r150' );
