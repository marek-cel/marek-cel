pkg load control
s = tf('s');
source( 'include_sys_tf_integrator_ideal.m' );
step(g);

source( 'include_sys_plot_step.m' );

print( gcf, '../sys_step_integrator_ideal.png', '-dpng', '-r150' );
