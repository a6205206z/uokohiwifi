#!/usr/bin/lua

local UOKO_AD_SERVICE_URL = "http://www.uoko.com/aboutus/contact/"
local UOKO_AD_LOCAL_FILE_PATH = "/www/uoko/add/ad.html"

function download_ad_page()
	local cmd = string.format("wget -O %s %s", UOKO_AD_LOCAL_PATH, UOKO_AD_SERVICE_URL)
	os.execute(cmd)
end



if arg[1] == "update" then
	if arg[2] == "ad" then
		download_ad_page()
	end	
end