pkg load control
s = tf('s');
source( 'include_sys_tf_integrator_ideal.m' );
bode(g);

source( 'include_sys_plot_bode.m' );

print( gcf, '../sys_bode_integrator_ideal.png', '-dpng', '-r150' );
