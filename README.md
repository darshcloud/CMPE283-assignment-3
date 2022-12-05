# CMPE 283 - Virtualization Technologies - Assignment 3 - Instrumentation via hypercall (Cont'd)

To modify the CPUID emulation code in KVM to report back additional information
when special CPUID leaf nodes are requested.
* For CPUID leaf node %eax=0x4FFFFFFE:<br/>
  Return the number of exits for the exit number provided (on input) in %ecx. This value should be returned in %eax
* For CPUID leaf node %eax=0x4FFFFFFF:<br/>
  Return the time spent processing the exit number provided (on input) in %ecx<br/>
  Return the high 32 bits of the total time spent for that exit in %ebx<br/>
  Return the low 32 bits of the total time spent for that exit in %ecx <br/>
  
  For leaf nodes 0x4FFFFFFE and 0x4FFFFFFF, if %ecx (on input) contains a value not defined by the
  SDM, return 0 in all %eax, %ebx, %ecx registers and return 0xFFFFFFFF in %edx. For exit types not
  enabled in KVM, return 0s in all four registers.

### Professor's Name: Michael Larkin <br/>
### Submitted By: Darshini Venkatesha Murthy Nag <br/>
### Student ID: 016668951 <br/>
### Linux kernel Source code Working tree: <br/> Please refer https://github.com/darshcloud/linux.git for the complete working tree which i forked from the master linux kernel repo and built the kernel to complete the assignment

## Steps used to complete the assignment
The environment setup (steps to build kernel and inner VM setup) is same as done in assignment 2
### Steps to build kernel:
* Fork the linux kernel source code repository https://github.com/torvalds/linux.git and clone it
* Install the dependencies using the below command <br/>
`sudo apt-get install fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison`
* Copy the existing configuration using the command<br/>
`cp -v /boot/config-$(uname -r) .config`
* Run the below command to compile and build the kernel<br/>
`make -j $nproc` <br/>
if you encounter error "No rule to make target 'debian/canonical-certs.pem"
then disable securities certificate by using<br/>
`scripts/config --disable SYSTEM_TRUSTED_KEYS` and `scripts/config --disable SYSTEM_REVOCATION_KEYS`
* Run the below command to install the required modules<br/>
`sudo make INSTALL_MOD_STRIP=1 modules_install`
* Run the below command to install the kernel<br/>
`sudo make install`
* Reboot and verify the kernel version by running the below command<br/>
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
* Code changes for this assignment are built on top of assignment 2 changes
* Added assignment functionality for building the leaf functions 0x4ffffffe and 0x4fffffff
* Added 2 Global variables exit_frequency and cycles_in_exit
* In vmx.c, implemented the changes for calculating the exit frequency
  and total time spent processing each exit in the vmx_handle_exit function
* In cpuid.c, created 2 new cpuid leaf in kvm_emulate_cpuid function which reads the
  exit_frequency of an exit into % eax when eax = 0x4ffffffe, ecx = exit number and moves the high 32 bits of cycles_in_exit into %ebx and low 32 bits
  of cycles_in_exit into %ecx when % eax = 0x4fffffff, ecx = exit number
* Compile the code using the below command<br/>
  `make -j $nproc modules`
* To install the built modules run the below command<br/>
  `sudo make INSTALL_MOD_STRIP=1 modules_install && make install`
* Run the below commands to reload the KVM module <br/>
`sudo rmmod kvm_intel ` <br/>
`sudo rmmod kvm` <br/>
`sudo modprobe kvm_intel` <br/>



## Output and Answers for Questions

  3. Comment on the frequency of exits – does the number of exits increase at a stable rate? Or are there
  more exits performed during certain VM operations? Approximately how many exits does a full VM
  boot entail?<br/>

  Answer: The frequency of the exits do not increase at a stable rate. As you can see in the below screenshot exits shot up at much difference rate each time i ran the   program and also while running other applications in the background. More exits are performed when i run different applications and open multiple browser windows.
  As per the below screenshotsfull VM boot entails ~ 3200000 exits

Before Boot

![VM_boot_entail](https://user-images.githubusercontent.com/111547793/205483894-cfa4e997-7a2c-4752-aa67-f6610112a82e.png)

After Boot

![VM_after_Reboot](https://user-images.githubusercontent.com/111547793/205483900-ca0487f7-4056-4399-bf8d-fef28102892d.png)

4. Of the exit types defined in the SDM, which are the most frequent? Least? <br/>

From the screenshots shown below we can see that

Most Frequent Exits are <br/>

Exit 48 - EPT Violation <br/>
Exit 32 - WRMSR <br/>
Exit 10 - CPUID <br/>
Exit 1 - External Interrupt <br/>
Exit 30 - I/O instruction <br/>


Least Frequent Exits are<br/>

Exit 55 - XSETBV<br/>
Exit 54 - WBINVD<br/>
Exit 29 - MOV DR<br/>

![exit_frequency_list](https://user-images.githubusercontent.com/111547793/205484143-3736b5d9-ecbc-4274-913b-5a8e41361cce.png)
![exit_frequency_list_1](https://user-images.githubusercontent.com/111547793/205484147-57246598-0858-48df-a95a-989bb4768c4b.png)
![exit_frequency_list_2](https://user-images.githubusercontent.com/111547793/205484152-18267518-b8de-4db0-853d-868c2a7da27a.png)
![exit_frequency_list_3](https://user-images.githubusercontent.com/111547793/205484154-97d501ef-85d8-492e-afb2-b4264a24bb69.png)


