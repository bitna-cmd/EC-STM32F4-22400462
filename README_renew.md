
### EXTI_enable()

Enables the specified EXTI line by unmasking its interrupt request.

```c
void EXTI_enable(PinName_t pinName);
```

**Parameters**

- **pinName:** GPIO pin identifier corresponding to the EXTI line (e.g., `PA_4`).

**Example code**

```c
EXTI_enable(PA_4);
```

<details>
<summary><b>View Implementation</b></summary>

```c
void EXTI_enable(PinName_t pinName) {
    GPIO_TypeDef *Port;
    unsigned int pin;
    ecPinmap(pinName, &Port, &pin);

    EXTI->IMR |= (1UL << pin);
}
```

</details>
