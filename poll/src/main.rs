use std::{io, net, thread};

fn main() {
    let (addr_1, addr_2) = create_addrs();
    thread::spawn(move || send_data(addr_1, addr_2).unwrap());
    recv_data(addr_1, addr_2).unwrap()
}

fn create_addrs() -> (net::SocketAddr, net::SocketAddr) {
    todo!("create two random socket addrs to communicate with")
}

fn send_data(addr_1: net::SocketAddr, addr_2: net::SocketAddr) -> io::Result<()> {
    _ = (addr_1, addr_2);
    todo!("send data to the specified addrs")
}

fn recv_data(addr_1: net::SocketAddr, addr_2: net::SocketAddr) -> io::Result<()> {
    // https://docs.rs/nix/latest/nix/poll
    #[allow(unused_imports)]
    use nix::poll;
    _ = (addr_1, addr_2);
    todo!("receive data from the specified addrs")
}
