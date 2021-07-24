pkg load control
s = tf('s');
source( 'include_sys_tf_differentiator_real.m' );
step(g);

source( 'include_sys_plot_step.m' );

print( gcf, '../sys_step_differentiator_real.png', '-dpng', '-r150' );
