# b64: Base64 Transcoder for Streams

This program is designed to encode and decode a typical Base64 stream from an
input stream.

Usage: `b64 [-e] [-d ASCII/binary] [-i if] [-o of]`

### Technical information

There are a few technical explanations in the header files. Otherwise, there
is some info here as well.

Default input stream is `stdin`.
Default output stream is `stdout`.

The implementation is quite rough but it seems to do the job. fgetc() loads 3
bytes into a 32-bit variable to force big-endian byte order. Then, B64 encoding
is performed using a 6-bit mask and bit shifts (the implementation can
**definitely** be improved) and the ASCII-encoded characters are send to the
output stream.

For decoding, a 32-bit variable is loaded with 3 bytes using fgetc() to force a
big-endian byte order. Then, depending on whether the output is specified to be
either ASCII or binary, the decoded data will be sent to the output stream.

### Todo:
- open stream as text if ASCII option specified(?)
