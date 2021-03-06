/* Usage: node gfx.js file.png w h output */
const fs = require("fs"); const Canvas = require('canvas'); const Image = Canvas.Image;
/* Pico-8 */
const palette = [ 
0, 0, 0, 
29, 43, 83, 
126, 37, 83, 
0, 135, 81,
171, 82, 54, 
95, 87, 79, 
194, 195, 199, 
255, 241, 232,
255, 0, 77, 
255, 163, 0, 
255, 236, 39, 
0, 228, 54,
41, 173, 255, 
131, 118, 156, 
255, 119, 168, 
255, 204, 170
]; 

let file = process.argv[2]; w = parseInt(process.argv[3]); h = parseInt(process.argv[4]);


if( !file ) { 
  console.log("Usage: node gfx.js file.png w h output"); 
}
else { 
  if (process.argv[5] == "") { 
    fs.writeFileSync( `${file.replace(/\..*$/, '')}.img`, Buffer.from( img4bpp( file, w, h ) ) ); 
  } 
  else { 
    fs.writeFileSync(process.argv[5], Buffer.from( img4bpp( file, w, h ) ) );
  } 
  console.log( `${file.replace(/\..*$/, '')}.img`); 
}

function img4bpp( path, w, h ){ 

	const canvas = Canvas.createCanvas(w, h); 
	const ctx = canvas.getContext('2d'); 
	const image = new Image(); image.src = fs.readFileSync( path );

    ctx.drawImage( image, 0, 0, w, h ); 
    const buf = canvas.toBuffer('raw'); 
    const pixel = [0,0,0]; 
    const infl = [];

	infl.push( w / 16 ); infl.push( w % 16 ); infl.push( h / 16 ); infl.push( h % 16 );

    let line = '';

    for( let i=0; i<buf.length; ++i ){

		let j;

		pixel[2] = buf[i++]; 
		pixel[1] = buf[i++]; 
		pixel[0] = buf[i++];


		let minind = 999;

		for( j=0; j<palette.length / 3; ++j ){

			if (Math.abs(pixel[0] - palette[j * 3]) < 4 && Math.abs(pixel[1] - palette[(j * 3) + 1]) < 4 && Math.abs(pixel[2] - palette[(j * 3) + 2]) < 4) {

				minind = j; 
				break; 
				
			}

		}

		if (minind == 999) { 
		  console.log("%i %i %i", w, h, buf.length); console.log("I: %i, X: %i, Y: %i - %i,%i,%i", i, 		((i/4)%w), ((i/4)/w), pixel[0], pixel[1], pixel[2] );

		}

		infl.push( minind );
		line += minind.toString(16); if (line.length == w ){ if (w % 2 == 1) {

        infl.push( 0 ); }

		// console.log(line);
		line = ''; }

    }

    const out = [];

    for( let i=0; i<infl.length; ) { 
      let hi = infl[i++]; 
      let lo = infl[i++]; 
      out.push( (hi<<4) | lo ); 
    }

    return out;

}