# YUV to Grayscale Frame Processor

This project reads a raw YUV 4:4:4 video frame from a file, converts it to RGB format, computes its grayscale equivalent, and writes the grayscale image to a new YUV file.

## 📂 File Structure

- `cat_498x332_444.yuv` — Input raw YUV 4:4:4 frame file.
- `cat_yuv_output.yuv` — Output file containing grayscale values as raw Y data.
- `main.c` — Source code to perform YUV to grayscale conversion.

## 📐 Frame Details

- Format: YUV 4:4:4
- Resolution: 498 x 332 (width x height)

## 🔧 Compilation

Use a C compiler like `gcc`:

```bash
gcc -o yuv_to_gray main.c -lm
▶️ Usage
Ensure cat_498x332_444.yuv is in the same directory. Then run:

bash
Copy
Edit
./yuv_to_gray
The grayscale output will be saved as cat_yuv_output.yuv.

⚙️ How It Works
Reading: Loads Y, U, and V components from the raw .yuv file.

Conversion: Converts YUV to RGB using standard conversion formulas.

Grayscale: Averages the RGB channels for grayscale value.

Writing: Outputs grayscale values as raw data to a .yuv file.

📋 Notes
Only the Y channel is used for grayscale output; U and V are ignored during writing.

The output is not a viewable image unless opened with software supporting raw grayscale (like FFmpeg or custom viewers).

📄 License
This project is provided for educational and research purposes.
