#!/usr/bin/lua

local UOKO_AD_SERVICE_URL = "http://www.uoko.com/aboutus/contact/"
local UOKO_DIR_PATH = "/www/uoko"
local UOKO_AD_LOCAL_DIR_PATH = "/www/uoko/ad" 
local UOKO_AD_LOCAL_FILE_PATH = "/www/uoko/ad/ad.html"

function file_exists(filepath)
  local f = io.open(filepath, "r")
  if f then
    f:close()
    return true
  else
    return false
  end
end

function mkdirr(dirpath)
  os.execute("mkdir -p '" .. dirpath .. "' -m777")
end

function download_ad_page()
	if not file_exists(UOKO_DIR_PATH) then
		mkdirr(UOKO_DIR_PATH)
	end

	if not file_exists(UOKO_AD_LOCAL_DIR_PATH) then
		mkdirr(UOKO_AD_LOCAL_DIR_PATH)
	end

	local cmd = string.format("wget -O %s %s", UOKO_AD_LOCAL_FILE_PATH, UOKO_AD_SERVICE_URL)
	os.execute(cmd)

	return 1,"download"
end



if arg[1] == "-u" then
	if arg[2] == "ad" then
		rc,msg = download_ad_page()
		print(msg)
		os.exit(rc)
	end
else
	print("Usage:")
	print(" uokohiwifi -u ad  	        -- update uoko ad to local server")
	os.exit(2)
end