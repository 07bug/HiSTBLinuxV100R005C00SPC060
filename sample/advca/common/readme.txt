1.tsplay demo
   executable program£ºsample_ca_tsplay
   source code:sample_ca_tsplay.c 
   introduction: this demo show the following functions
                 1> loading clear CW or loading encrypted CWPK and encrypted CWs onto the chipset
                 2> processing of a scrambled transport stream and rendering the descrambled and decoded video on a display
                 The video data can be output through CVBS YPBPR or HDMI interface.
   usage: sample_ca_tsplay cw_key_config.ini tsfile
   if there is more than one program in the tsfile, you can select program by number.
   The cw_key_config.ini may contain keywords below:
    #For use clear cw or encrypted cw, YES or NO
    ENCRYPTCW = "YES"

    #Which keyladder use to descramber
    KLADTYPE = "CSA2"

    #Keyladder algorithm TDES or AES
    KLADALG  = "AES"
    
    #Encrypted cwpk
    SESSIONKEY1 = "A8E17FA05F9E47FF16110B594F7C17F6"
    SESSIONKEY2 = ""

    #Encrypted cw
    ENCRYPTEDODDKEY = "12C0B61BD7A5B5627AD87BE6959A61E6"
    ENCRYPTEDEVENKEY  = "09262CC117D861A84924ACBD113E6E81"

    #Clear cw    
    CLEARODDKEY       = "FE172C41A2E1D457"
    CLEAREVENKEY      = "D42282781D2872B7"

2.dvbplay demo
   executable program£ºsample_ca_dvbplay
   source code:sample_ca_dvbplay.c 
   introduction:this demo show the following functions
                 1> loading clear CW or loading encrypted CWPK and encrypted CWs onto the chipset
                 2> processing of a scrambled transport stream and rendering the descrambled and decoded video on a display
                 The video data can be output through CVBS YPBPR or HDMI interface.
   usage: sample_ca_dvbplay cw_key_config.ini freq
   The cw_key_config.ini may contain keywords below:
   #For use clear cw or encrypted cw, YES or NO
   ENCRYPTCW = "YES"

   #Which keyladder use to descramber
   KLADTYPE = "CSA2"

   #Keyladder algorithm TDES or AES
   KLADALG  = "AES"
    
   #Encrypted cwpk
   SESSIONKEY1 = "A8E17FA05F9E47FF16110B594F7C17F6"
   SESSIONKEY2 = ""

   #Encrypted cw
   ENCRYPTEDODDKEY = "12C0B61BD7A5B5627AD87BE6959A61E6"
   ENCRYPTEDEVENKEY  = "09262CC117D861A84924ACBD113E6E81"

   #Clear cw    
   CLEARODDKEY       = "FE172C41A2E1D457"
   CLEAREVENKEY      = "D42282781D2872B7"      
     
3.encrypt demo
   executable program£ºsample_ca_crypto
   source code:sample_ca_crypto.c 
   introduction:this demo show the following functions
                1> encrypting data user keyladder.
   usage: sample_ca_crypto crypto_key_config.ini
   The crypto_key_config.ini may contain keywords below:
   #For encrypt or decrypt
    #Which keyladder to use for encrypt or decrypt.
    KLADTYPE = "MISC"

    #The keyladder algorithm, AES or TDES, mode is fix to ECB
    KLADALG  = "TDES"

    #Encrypt or decrypt algorithm, the valid algorithm is AES, TDES
    Algorithm= "AES"

    #The Mode value is for AES and TDES
    #The valid Mode for AES is ECB,CBC
    #The valid Mode for TDES is ECB,CBC
    Mode= "CBC"

    #Data to be encrypted
    PLAINTTEXT   = "1234567800000000000000000000000000000000000000000000000000000000"

    #Keyladder session keys
    SESSIONKEY1  = "1f0e0d0c0b0a09080706050403020100"
    SESSIONKEY2  = "2f0e0d0c0b0a09080706050403020100"
    SESSIONKEY3  = "3f0e0d0c0b0a09080706050403020100"
    SESSIONKEY4  = "4f0e0d0c0b0a09080706050403020100"

    #Content key
    CONTENTKEY   = "0f0e0d0c0b0a09080706050403020100"
   
4.RSAkey demo
executable program: sample_ca_writeRSAkey
source code:sample_ca_writeRSAkey.c
introduction: show how to set RSAkey
usage: sample_ca_writeRSAkey 


5.Set OTP fuse
executable program: sample_ca_set_otp_fuse
source code:sample_ca_set_otp_fuse.c
introduction: set OTP fuse
usage: sample_ca_set_otp_fuse name value

6.Get OTP fuse
executable program: sample_ca_get_otp_fuse
source code:sample_ca_get_otp_fuse.c
introduction: show how to get otp fuse status
usage: sample_ca_get_otp_fuse

7.encrypt boot demo
executable program: sample_ca_blpk
source code:sample_ca_blpk.c
introduction: show how to encrypt boot and burn it to flash
usage: sample_ca_blpk

