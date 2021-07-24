pkg load control
s = tf('s');
source( 'include_sys_tf_second_order_lag.m' );
step(g);

source( 'include_sys_plot_step.m' );

print( gcf, '../sys_step_second_order_lag.png', '-dpng', '-r150' );
