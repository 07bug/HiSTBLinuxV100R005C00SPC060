����������չʾʵ��VI��VI-VO�ػ�����
�����ʽ��sample_vi [vo_format] [Width] [Height] [X] [Y] [VideoFormat]
����˵����vo_format ��Ƶ�����ʽ ȡֵ��Χ 1080P_60 | 1080P_50 | 1080i_60 | 1080i_50 | 720P_60 ��ѡ Ĭ��ֵ720P_50
					VideoFormat: ��Ƶ���ظ�ʽ ȡֵ��Χ 0:YUV422 | 1:YUV420 ��ѡ Ĭ��ֵ1:YUV420
��    �ӣ�sample_vi 720P_50 600 400 90 80 0
ע�����
HI3798ϵ��IC
1.sample����ǰ��Ҫ����hi_hdmirx.ko��
HI3716CV200ϵ��IC��
1.�ֶ�����SIL9293.KO����insmod pub/kmod/hi_sil9293.ko�� ��
2.ȷ��HDMI�����ź���SIL9293оƬ����ȷ���ӡ�
3.���ѡ�á�hi3716cdmo2f_hi3716cv200_ddr3_2gbyte_8bitx4_4layers_XXX.reg�����¹ܽŸ���ΪĬ�����á�
���ѡ�����������ļ���Ҫ�ֶ����йܽŸ������á�

a.ȷ��SIL9293ʹ�õ���GPIO�ܽ�����ȷ���ã�����I2C_SCL,I2C_SDA,int,reset
���ʹ��HI3716CV200ESоƬ���ܽŸ��������������£�
himm 0xf8a2104c 0x0   (GPIO2_3   I2C_SCL)
himm 0xf8a21050 0x0   (GPIO2_4   I2C_SDA)
himm 0xf8a21040 0x0   (GPIO2_0   RESET)
himm 0xf8a21044 0x0   (GPIO2_1   INT)
���ʹ��HI3716CV200оƬ���ܽŸ��������������£�
 A.ѡ��Ӳ��I2c (Ĭ������) 
himm 0xf8a2104c 0x5   (GPIO2_3   I2C_SDA)
himm 0xf8a21050 0x5   (GPIO2_4   I2C_SCL)
 B.ѡ�����I2c 
himm 0xf8a2104c 0x0   (GPIO2_3   I2C_SDA)
himm 0xf8a21050 0x0   (GPIO2_4   I2C_SCL)

b.gpio�ܽŸ�������
himm 0xf8a21128 0x0   (GPIO10_2  RESET)
himm 0xf8a21124 0x0   (GPIO10_1  INT)

c.ȷ��VI�ܽŸ�������ȷ���ã�����clk,de,filed,hsync,vsync,dat0~dat15
���ʹ��HI3716CV200ESоƬ���ܽŸ��������������£�
himm 0xf8a210d4 0x5
himm 0xf8a2106c 0x5
himm 0xf8a21070 0x5
himm 0xf8a21014 0x5
himm 0xf8a21018 0x5
himm 0xf8a210c0 0x5
himm 0xf8a210d0 0x5
himm 0xf8a210ec 0x5
himm 0xf8a210e8 0x5
himm 0xf8a2105c 0x5
himm 0xf8a210b8 0x5
himm 0xf8a210b4 0x5
himm 0xf8a210b0 0x5
himm 0xf8a210bc 0x5
himm 0xf8a210cc 0x5
himm 0xf8a210c8 0x5
himm 0xf8a210c4 0x5
himm 0xf8a210e0 0x5
himm 0xf8a210d8 0x5
himm 0xf8a210dc 0x5
himm 0xf8a210e4 0x5
���ʹ��HI3716CV200оƬ���ܽŸ��������������£�
himm 0xf8a21074 0x5
himm 0xf8a21078 0x5
himm 0xf8a2107c 0x5
himm 0xf8a21080 0x5
himm 0xf8a21084 0x5
himm 0xf8a21088 0x5
himm 0xf8a2108c 0x5
himm 0xf8a21090 0x5
himm 0xf8a21094 0x5
himm 0xf8a21098 0x5
himm 0xf8a2109c 0x5
himm 0xf8a210d8 0x5
himm 0xf8a210dc 0x5
himm 0xf8a210e0 0x5
himm 0xf8a210e4 0x5
himm 0xf8a21040 0x105
himm 0xf8a21044 0x5
himm 0xf8a21048 0x5
himm 0xf8a2106c 0x5
himm 0xf8a21070 0x5