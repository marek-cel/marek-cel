pkg load control
s = tf('s');
source( 'include_sys_tf_proportional.m' ); %sic!
step(g); %sic!

source( 'include_sys_plot_impulse.m' );

print( gcf, '../sys_impulse_integrator_ideal.png', '-dpng', '-r150' );
