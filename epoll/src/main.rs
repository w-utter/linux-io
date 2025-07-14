use std::{io, path, thread};

fn main() {
    let (path_1, path_2) = create_paths();
    recv_data(path_1, path_2).unwrap()
}

fn create_paths() -> (path::PathBuf, path::PathBuf) {
    todo!("create two random paths to character devices to read from")
}

fn recv_data(path_1: path::PathBuf, path_2: path::PathBuf) -> io::Result<()> {
    // https://docs.rs/epoll-rs/latest/epoll_rs
    #[allow(unused_imports)]
    use epoll_rs;
    _ = (path_1, path_2);
    todo!("receive data from the specified paths")
}
