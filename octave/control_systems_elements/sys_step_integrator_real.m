pkg load control
s = tf('s');
source( 'include_sys_tf_integrator_real.m' );
step(g);

source( 'include_sys_plot_step.m' );

print( gcf, '../sys_step_integrator_real.png', '-dpng', '-r150' );
