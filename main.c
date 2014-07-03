#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include <linux/power_ic.h>
#include <fcntl.h>

#define STANDARD 0

int main(int argc, char *argv[]);
void _vibrate(int duration);
void _delay(int msec);
int in_msec_range_q(int msec);
int in_count_range_q(int cnt);
int is_only_digits_arg_q(char *arg);
int call_vibro_func(char *arg);
void print_error(int err);
void print_help();
void standard_vibro();
void helicopter_vibro();
void ufo_vibro();
void shock_vibro();
void mosquito_vibro();
void train_vibro();
void pulse_vibro();

static struct modes {
    const char *name_mode;
    const int count_it;
    void (*vibro_func)();
} vibro_mode[] = {
{ "standard", 3, standard_vibro },
{ "helicopter", 3, helicopter_vibro },
{ "ufo", 3, ufo_vibro },
{ "shock", 2, shock_vibro },
{ "mosquito", 6, mosquito_vibro },
{ "train", 3, train_vibro },
{ "pulse", 3, pulse_vibro }
};

int main(int argc, char *argv[])
{
    switch (argc) {
    case 1: {
        vibro_mode[STANDARD].vibro_func(); // Call standard vibro function
        break;
    }
    case 2: {
        if (!is_only_digits_arg_q(argv[1])) {
            if (!call_vibro_func(argv[1])) {
                print_help();
            }
        } else {
            int msec = atoi(argv[1]);
            if (!in_msec_range_q(msec)) {
                print_error(0);
                return 1;
            } else {
                _vibrate(msec);
            }
        }
        break;
    }
    case 3: {
        if (!is_only_digits_arg_q(argv[1]) && is_only_digits_arg_q(argv[2])) {
            int i, j = 0;
            int count = atoi(argv[2]);

            if (!in_count_range_q(count)) {
                print_error(1);
                return 2;
            }

            for (i = 0; i < count; ++i) {
                if (!call_vibro_func(argv[1])) {
                    ++j;
                }
                _delay(350);
            }

            if (j) {
                print_help();
            }
        }
        else {
            print_help();
        }
        break;
    }
    default: {
        print_help();
        break;
    }
    }
    return 0;
}

int in_msec_range_q(int msec)
{
    return (msec < 15 || msec > 60000) ? 0 : 1;
}

int in_count_range_q(int cnt)
{
    return (cnt < 2 || cnt > 10) ? 0 : 1;
}

int is_only_digits_arg_q(char *arg)
{
    int i, size = strlen(arg);
    for (i = 0; i < size; ++i) {
        if (!isdigit(arg[i])) {
            return 0;
        }
    }
    return 1;
}

int call_vibro_func(char *arg)
{
    int i;
    char *_arg = strtok(strdup(arg), "-");
    int modes_count = sizeof(vibro_mode) / sizeof(vibro_mode[0]);
    for (i = 0; i < modes_count; ++i) {
        if (_arg) {
            if (!strcmp(_arg, vibro_mode[i].name_mode)) {
                vibro_mode[i].vibro_func();
                return 1;
            }
        }
    }
    return 0;
}

void _vibrate(int duration)
{
    int power_ic = open("/dev/" POWER_IC_DEV_NAME, O_RDWR);
    ioctl(power_ic, POWER_IC_IOCTL_PERIPH_SET_VIBRATOR_ON,1);
    usleep(duration * 1000);
    ioctl(power_ic, POWER_IC_IOCTL_PERIPH_SET_VIBRATOR_ON,0);
    close(power_ic);
}

void print_error(int err)
{
    switch (err) {
    case 0: {
        printf("ERROR: Wrong range!\n"
               "\tThe msec should be in the range 15...60000\n");
        break;
    }
    case 1: {
        printf("ERROR: Wrong range!\n"
               "\tThe count should be in the range 2...10\n");
        break;
    }
    default: {
        printf("ERROR: Unknown error!\n");
        break;
    }
    }

    print_help();
}

void print_help()
{
    printf("Please use:\n"
           "\tzPulse\n"
           "\tzPulse [duration-in-msec]\n"
           "\tzPulse [mode]\n"
           "\tzPulse [mode] [count]\n"
           "Available modes:\n"
           "\t- standard\n"
           "\t- helicopter\n"
           "\t- ufo\n"
           "\t- shock\n"
           "\t- mosquito\n"
           "\t- train\n"
           "\t- pulse\n"
           "Examples:\n"
           "\tzPulse 15\n"
           "\tzPulse 3000\n"
           "\tzPulse mosquito\n"
           "\tzPulse -ufo 6\n"
           "\tzPulse --pulse 2\n");
}

void _delay(int msec)
{
    usleep(msec * 1000);
}

void standard_vibro()
{
    printf("Standard vibro\n");
    _vibrate(500);
    _vibrate(500);
}

void helicopter_vibro()
{
    printf("Helicopter vibro\n");
    _vibrate(75);
    _delay(100);
    _vibrate(100);
    _delay(100);
    _vibrate(75);
    _delay(100);
    _vibrate(100);
    _delay(100);
    _vibrate(75);
    _delay(100);
    _vibrate(100);
}

void ufo_vibro()
{
    printf("Ufo vibro\n");
    _vibrate(200);
    _delay(300);
    _vibrate(100);
    _delay(300);
    _vibrate(200);
}

void shock_vibro()
{
    printf("Shock vibro\n");
    _vibrate(35);
    _delay(100);
    _vibrate(200);
    _delay(300);
    _vibrate(35);
    _delay(100);
    _vibrate(200);
    _delay(300);
    _vibrate(35);
    _delay(100);
    _vibrate(200);
}

void mosquito_vibro()
{
    printf("Mosquito vibro\n");
    _vibrate(15);
    _delay(150);
    _vibrate(35);
    _delay(150);
    _vibrate(55);
    _delay(150);
    _vibrate(75);
    _delay(150);
    _vibrate(95);
    _delay(150);
    _vibrate(75);
    _delay(150);
    _vibrate(55);
    _delay(150);
    _vibrate(35);
    _delay(150);
    _vibrate(15);
}

void train_vibro()
{
    printf("Train vibro\n");
    _vibrate(75);
    _vibrate(100);
    _delay(100);
    _vibrate(100);
    _vibrate(75);
}

void pulse_vibro()
{
    printf("Pulse vibro\n");
    _vibrate(150);
    _delay(150);
    _vibrate(150);
    _delay(500);
    _vibrate(150);
    _delay(150);
    _vibrate(150);
}
