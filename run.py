import subprocess
import pywaifu2x
import time

print ('='*32)
'''
line = 'time ./waifu2x-ncnn-vulkan -i ../../../hires.png -o hires2.png -n 3 -m /mnt/ssd1t/Anime/waifu2x-ncnn-vulkan/models/models-upconv_7_anime_style_art_rgb/ -g 2'
res = subprocess.run(line.split(), stdout=subprocess.PIPE)
print(str(res.stderr))
print(str(res.stdout))
lines_iterator = iter(res.stdout.readline, b"")
while res.poll() is None:
    for line in lines_iterator:
        nline = line.rstrip()
        print(nline.decode("latin"), end = "\r\n",flush =True)
'''

waifu2x = pywaifu2x.pywaifu2x(2)

print (dir(waifu2x))
print ('='*32)

bin = '/mnt/ssd1t/Anime/waifu2x-ncnn-vulkan/models/models-cunet/noise3_scale2.0x_model.bin'
param = '/mnt/ssd1t/Anime/waifu2x-ncnn-vulkan/models/models-cunet/noise3_scale2.0x_model.param'
print( len(bin),len(param))
waifu2x.set_noise(3)
waifu2x.set_scale(2)
waifu2x.set_tilesize(256)
waifu2x.set_prepadding(18)
print (waifu2x.get_noise())
#waifu2x.init_ncnn()
waifu2x.load(param,bin)
print ('='*32)

input = '/mnt/ssd1t/upir.jpg'
output = '/mnt/ssd1t/pyout.png'

N = 1
start = time.time()
for i in range(N):
    waifu2x.predict(input,output)
print ('Time:', (time.time()-start)/N)

print ('='*32)
waifu2x = 0
print ('='*32)