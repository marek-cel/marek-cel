pkg load control
s = tf('s');
source( 'include_sys_tf_lead_lag.m' );
step(g);

source( 'include_sys_plot_step.m' );

print( gcf, '../sys_step_lead_lag.png', '-dpng', '-r150' );
