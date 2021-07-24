pkg load control
s = tf('s');
source( 'include_sys_tf_proportional.m' );
bode(g);

source( 'include_sys_plot_bode.m' );

print( gcf, '../sys_bode_proportional.png', '-dpng', '-r150' );
