#include <stdint.h>
#include <stdio.h>

static inline void native_cpuid(unsigned int *eax, unsigned int *ebx,
                                unsigned int *ecx, unsigned int *edx)
{
        /* ecx is often an input as well as an output. */
        asm volatile("cpuid"
            : "=a" (*eax),
              "=b" (*ebx),
              "=c" (*ecx),
              "=d" (*edx)
            : "0" (*eax), "2" (*ecx));
}

int main()
{
	uint64_t exit_time;
	uint32_t eax, ebx, ecx, edx;
	int i;

	for (i=0; i<70; i++) {
		eax = 0x4ffffffe;
		ecx = i;
		ebx = edx = 0;
		native_cpuid(&eax, &ebx, &ecx, &edx);
		printf("CPUID 0x4ffffffe, Exit No: %d Exit Frequency = %d\n", i, eax);
		eax = 0x4fffffff;
		ecx = i;
		ebx = edx = 0;
		native_cpuid(&eax, &ebx, &ecx, &edx);
		exit_time = ebx;
		exit_time = exit_time << 32;
		exit_time |= ecx;
		printf("CPUID 0x4fffffff, Exit No: %d, Total time spent processing the exit = %ld\n", i, exit_time);
	}
	return 0;
}
