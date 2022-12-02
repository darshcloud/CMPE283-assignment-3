# CMPE 283 - Virtualization Technologies - Assignment 3 - Instrumentation via hypercall (Cont'd)

To modify the CPUID emulation code in KVM to report back additional information
when special CPUID leaf nodes are requested.
* For CPUID leaf node %eax=0x4FFFFFFE:<br/>
  Return the number of exits for the exit number provided (on input) in %ecx. This value should be returned in %eax
* For CPUID leaf node %eax=0x4FFFFFFF:<br/>
  Return the time spent processing the exit number provided (on input) in %ecx<br/>
  Return the high 32 bits of the total time spent for that exit in %ebx<br/>
  Return the low 32 bits of the total time spent for that exit in %ecx

### Professor's Name: Michael Larkin <br/>
### Submitted By: Darshini Venkatesha Murthy Nag <br/>
### Student ID: 016668951 <br/>
### Linux kernel Source code Working tree: <br/> Please refer https://github.com/darshcloud/linux.git for the complete working tree

## Steps used to complete the assignment
The environment setup (steps to build kernel and inner VM setup) is same as done in assignment 2
### Steps to build kernel:
* Fork the linux kernel source repository https://github.com/torvalds/linux.git and clone it
* Install the dependencies using the below command <br/>
`sudo apt-get install fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison`
* Copy the existing configuration using the command<br/>
`cp -v /boot/config-$(uname -r) .config`
* run the below command to compile and build the kernel<br/>
`make -j $nproc` <br/>
if you encounter error "No rule to make target 'debian/canonical-certs.pem"
then disable securities certificate by using<br/>
`scripts/config --disable SYSTEM_TRUSTED_KEYS` and `scripts/config --disable SYSTEM_REVOCATION_KEYS`
* Run the below command to install the required modules<br/>
`sudo make INSTALL_MOD_STRIP=1 modules_install`
* Run the below command to install the kernel<br/>
`sudo make install`
* Reboot and verify the kernel version by running the command<br/>
`uname -mrs`

### Inner VM Setup
* Before installing the KVM first check whether CPU virtualization feature is enabled in the system BIOS or not by running the below command <br/>
`egrep -c '(vmx|svm)' /proc/cpuinfo`
* Install the QEMU/KVM and Libvirt using the below command <br/>
`sudo apt install qemu-kvm libvirt-clients libvirt-daemon-system bridge-utils virtinst libvirt-daemon`
* Start and enable KVM service <br/>
`sudo systemctl enable --now libvirtd`
* Install Virt-Manager GUI for KVM using the below command <br/>
`sudo apt install virt-manager -y`
* Download the ubuntu iso image
* Run the KVM Virt-Manager and create a VM
* Complete the installation process and configure the inner VM
* Build the test code inside the inner VM to test the changes made in the Outer VM kvm module.

### Code Modification in Kernel source code




### Output

## Questions
