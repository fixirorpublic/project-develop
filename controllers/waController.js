const { Client, LocalAuth } = require('whatsapp-web.js');
const qrcode = require('qrcode-terminal');

const client = new Client({
    authStrategy: new LocalAuth()
});

client.on('qr', (qr) => {
    qrcode.generate(qr, {small: true});
    //console.log('QR RECEIVED', qr);
});

client.on('ready', () => {
    console.log('Client is ready!');
});

client.initialize();

const api = async (req,res) => {
    let nohp = req.query.nohp || req.body.nohp;
    let token1 = req.query.token || req.body.token;
    const pesan = req.query.pesan || req.body.pesan;
    const token = "KNSDKSNDFDKPnpnpnmpljnaslckn"

    if(token1 !== token) {
        return res.status(401).json({ status: "gagal",  pesan: "token tidak valid"})
    }
    //6281229563543@c.us

    try {

        if(nohp.startsWith("0")){
            nohp= "62" + nohp.slice(1) + "@c.us";
        } else if (nohp.startsWith("62")) {
            nohp = nohp + "@c.us";
        } else {
            nohp = "62" + nohp + "@c.us";
        }


        const user = await client.isRegisteredUser(nohp);

        if(user){
            client.sendMessage(nohp, pesan);
            res.json({ status : "berhasil terkirim", pesan})
        } else {
            res.json({ status: "gagal", pesan: "nomor whatsapp tidak terdaftar"})
        }  
    } catch (error) {
        console.log(error);
        res.status(500).json({ status: "error", pesan: "error server"});

    }

    
}

module.exports = api