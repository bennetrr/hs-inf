window.addEventListener("load", () => {
    //region Elements
    /** @type {HTMLFormElement}*/
    const form = document.getElementById("contact-form");
    /** @type {HTMLSpanElement}*/
    const submitStatus = document.getElementById("submit-status");

    /** @type {HTMLInputElement}*/
    const vornameField = document.getElementById("vorname");
    /** @type {HTMLDivElement}*/
    const vornameContainer = document.getElementById("vorname-container");
    /** @type {HTMLSpanElement}*/
    const vornameError = document.getElementById("vorname-error");

    /** @type {HTMLInputElement}*/
    const nachnameField = document.getElementById("nachname");
    /** @type {HTMLDivElement}*/
    const nachnameContainer = document.getElementById("nachname-container");
    /** @type {HTMLSpanElement}*/
    const nachnameError = document.getElementById("nachname-error");

    /** @type {HTMLInputElement}*/
    const emailField = document.getElementById("email");
    /** @type {HTMLDivElement}*/
    const emailContainer = document.getElementById("email-container");
    /** @type {HTMLSpanElement}*/
    const emailError = document.getElementById("email-error");

    /** @type {HTMLTextAreaElement}*/
    const nachrichtField = document.getElementById("nachricht");
    /** @type {HTMLDivElement}*/
    const nachrichtContainer = document.getElementById("nachricht-container");
    /** @type {HTMLSpanElement}*/
    const nachrichtError = document.getElementById("nachricht-error");
    //endregion

    //region Validators
    /**
     * @param {string} name
     * @param {HTMLInputElement} field
     * @param {HTMLDivElement} container
     * @param {HTMLSpanElement} error
     * */
    function validateName(name, field, container, error) {
        if (field.value.trim() === "") {
            container.dataset.valid = 'false';
            error.replaceChildren(document.createTextNode(`${name} darf nicht leer sein!`));
            return false;
        }
        if (field.value.match(/[0-9]/)) {
            container.dataset.valid = 'false';
            error.replaceChildren(document.createTextNode(`${name} darf keine Nummern enthalten!`));
            return false;
        }

        container.dataset.valid = 'true';
        error.replaceChildren();
        return true;
    }

    function validateEmail() {
        if (emailField.value.trim() === "") {
            emailContainer.dataset.valid = 'false';
            emailError.replaceChildren(document.createTextNode('Email darf nicht leer sein!'));
            return false;
        }
        if (!emailField.value.match(/^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/)) {
            emailContainer.dataset.valid = 'false';
            emailError.replaceChildren(document.createTextNode('Email ist ungültig!'));
            return false;
        }

        emailContainer.dataset.valid = 'true';
        emailError.replaceChildren();
        return true;
    }

    function validateNachricht() {
        if (nachrichtField.value.trim() === "") {
            nachrichtContainer.dataset.valid = 'false';
            nachrichtError.replaceChildren(document.createTextNode('Nachricht darf nicht leer sein!'));
            return false;
        }

        nachrichtContainer.dataset.valid = 'true';
        nachrichtError.replaceChildren();
        return true;
    }
    //endregion

    //region Blur Events
    vornameField.addEventListener('blur', () => {
        validateName('Vorname', vornameField, vornameContainer, vornameError);
    });

    nachnameField.addEventListener('blur', () => {
        validateName('Nachname', nachnameField, nachnameContainer, nachnameError);
    });

    emailField.addEventListener('blur', () => {
        validateEmail();
    });

    nachrichtField.addEventListener('blur', () => {
        validateNachricht();
    });
    //endregion

    //region Form Events
    form.addEventListener('submit', (event) => {
        const vornameValid = validateName('Vorname', vornameField, vornameContainer, vornameError);
        const nachnameValid = validateName('Nachname', nachnameField, nachnameContainer, nachnameError);
        const emailValid = validateEmail();
        const nachrichtValid = validateNachricht();

        if (vornameValid && nachnameValid && emailValid && nachrichtValid) {
            form.reset();
            submitStatus.replaceChildren(document.createTextNode('Formular erfolgreich abgesendet!'));
            submitStatus.style.color = 'var(--green)';
            setTimeout(() => submitStatus.replaceChildren(), 5000);
        } else {
            submitStatus.replaceChildren(document.createTextNode('Senden fehlgeschlagen, bitte Eingaben überprüfen!'));
            submitStatus.style.color = 'var(--primary1)';
            event.preventDefault();
        }
    });

    form.addEventListener('reset', (event) => {
        delete vornameContainer.dataset.valid;
        vornameError.replaceChildren();

        delete nachnameContainer.dataset.valid;
        nachnameError.replaceChildren();

        delete emailContainer.dataset.valid;
        emailError.replaceChildren();

        delete nachrichtContainer.dataset.valid;
        nachrichtError.replaceChildren();

        submitStatus.replaceChildren();
    });
    //endregion
});
