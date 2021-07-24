pkg load control
s = tf('s');
source( 'include_sys_tf_differentiator_real.m' );
bode(g);

source( 'include_sys_plot_bode.m' );

print( gcf, '../sys_bode_differentiator_real.png', '-dpng', '-r150' );
