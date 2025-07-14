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
    _ = files;
    todo!("read in files")
}
