pkg load control
s = tf('s');
source( 'include_sys_tf_integrator_real.m' );
impulse(g);

source( 'include_sys_plot_impulse.m' );

print( gcf, '../sys_impulse_integrator_real.png', '-dpng', '-r150' );
