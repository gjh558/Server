

               FFMPEG FULL SDK V2.0

               ffmpeg工程组 20060925

    在ffmpeg工程组2006年5月5日发布ffmpeg+x264 SDK V1.0之后，

很多热心的朋友提出了不少的建议与要求，经过精心的准备与策划，

ffmpeg工程组再次发布FFMPEG FULL SDK V2.0，此次发布的SDK为

Full SDK，我们尽可能的集成更多的编解码器。

    该SDK的编译配置如下：

Configured with:
" --enable-mingw32 --enable-shared --disable-static
--enable-memalign-hack --enable-a52 --enable-dts --enable-faac
--enable-faad --enable-mp3lame --enable-amr_nb --enable-amr_nb-fixed
--enable-x264 --enable-libogg --enable-avisynth --enable-gpl
--extra-cflags=-I/usr/local/include --extra-ldflags=-L/usr/local/lib "

    该SDK具备解码wmv9 and wmv7/8,rmvb(by avisynth support)
等码流的能力，不过你需要安装avisynth2.56。


    SDK的使用方法可参考ffmpeg项目中的output_example.c和

libavcodec目录下的apiexample.c以及ffmpeg.c等例程源代码。

    我们将继续发布更强大、更稳定的ffmpeg SDK，请继续关注

ffmpeg工程组（http://bbs.chinavideo.org）


版本：
    ffmpeg：V0.4.9 pre1 (SVN update:2006-09-22 r6315)

源代码：
    该SDK并不提供ffmpeg的全部源代码，如果需要，可以通过如下
两种方式获得：
    1、从中华视频网下载之前版本的ffmpeg源代码：
        http://www.chinavideo.org/
    2、采用subversion获取最新的源代码：
        svn://svn.mplayerhq.hu/ffmpeg/trunk

疑问：

    如果在使用过程中遇到疑难问题，可以通过如下方式得到相关
的技术支持：

    ffmpeg工程组：http://bbs.chinavideo.org
    ffmpeg工程组QQ群：6939161，27548839
    AnyChat视频会议室：http://www.anychat.cn

感谢：

    该SDK最终由ffmpeg工程组成员Fastreaming编译，有任何问题

大家可以通过下面的方式与之联系：

--
Skype: fastreaming
GTalk:  fastreaming
MSN:   dev@fastreaming.com
Mail:    codec@fastreaming.com
 ******We are here just for you******




                        中华视频网：  http://www.chinavideo.org
                        ffmpeg工程组：http://bbs.chinavideo.org
                                  2006年9月25日