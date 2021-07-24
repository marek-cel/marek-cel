pkg load control
s = tf('s');
source( 'include_sys_tf_first_order_lead.m' );
bode(g);

source( 'include_sys_plot_bode.m' );

print( gcf, '../sys_bode_first_order_lead.png', '-dpng', '-r150' );
