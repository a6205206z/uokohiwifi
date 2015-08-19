#!/usr/bin/lua

local UOKO_AD_SERVICE_URL = "http://www.uoko.com/aboutus/contact/"
local UOKO_DIR_PATH = "/www/uoko"
local UOKO_AD_LOCAL_DIR_PATH = "/www/uoko/ad" 
local UOKO_AD_LOCAL_FILE_PATH = "/www/uoko/add/ad.html"

function download_ad_page()
	if not file_exists(UOKO_DIR_PATH) then
		local mkdircmd = string.format("mkdir %s",UOKO_DIR_PATH)
		os.execute(mkdircmd)
	end

	if not file_exists(UOKO_AD_LOCAL_DIR_PATH) then
		local mkdircmd = string.format("mkdir %s",UOKO_AD_LOCAL_DIR_PATH)
		os.execute(mkdircmd)
	end

	local cmd = string.format("wget -O %s %s", UOKO_AD_LOCAL_FILE_PATH, UOKO_AD_SERVICE_URL)
	os.execute(cmd)
end



if arg[1] == "-u" then
	if arg[2] == "ad" then
		download_ad_page()
	end	
end