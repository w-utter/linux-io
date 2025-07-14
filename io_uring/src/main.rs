use std::{fs, io, time};

fn main() {
    let now = time::Instant::now();
    let files = generate_files();
    read_files(&files).unwrap();
    let elapsed = now.elapsed();
    println!("read {} files in {elapsed:?}", files.len())
}

fn generate_files() -> Vec<fs::File> {
    todo!("generate a list of files to read")
}

fn read_files(files: &[fs::File]) -> io::Result<()> {
    // https://docs.rs/io-uring/latest/io_uring
    #[allow(unused_imports)]
    use io_uring;
    _ = files;
    todo!("read in files")
}
