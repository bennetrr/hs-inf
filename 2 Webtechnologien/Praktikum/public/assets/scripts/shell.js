const NAVIGATION_ANIMATION_LENGTH = 400;

class PortfolioShell extends HTMLElement {
    static observedAttributes = ['hide-aside'];

    constructor() {
        super();
        this.hideAside = false;
    }

    async mountTemplate() {
        const response = await fetch('/assets/templates/shell.template.html');

        const wrapper = document.createElement('div');
        wrapper.innerHTML = await response.text();
        document.body.appendChild(wrapper);

        this.attachShadow({ mode: "open" });
        this.shadowRoot.appendChild(document.getElementById('shell-template').content.cloneNode(true));

        if (this.hideAside) {
            this.shadowRoot.querySelector('aside').style.display = 'none';
        }
    }

    setupNavigation() {
        // Set the nav-current class to the right link
        this.shadowRoot.querySelector(`.nav-link[href="${window.location.pathname}"]`).classList.add('nav-current');

        // Set up mobile navigation
        this.shadowRoot.getElementById('nav-hamburger').addEventListener('click', () => {
            const shellElement = this.shadowRoot.querySelector('.shell');

            switch (shellElement.dataset.navState) {
                case 'open':
                    shellElement.dataset.navState = 'closing';
                    setTimeout(() => {
                        shellElement.dataset.navState = 'closed';
                    }, NAVIGATION_ANIMATION_LENGTH);
                    break;
                case 'closed':
                    shellElement.dataset.navState = 'opening';
                    setTimeout(() => {
                        shellElement.dataset.navState = 'open';
                    }, NAVIGATION_ANIMATION_LENGTH);
                    break;
            }
        });
    }

    setPageTitle() {
        const mobileTitleElement = this.shadowRoot.getElementById('page-title');

        switch (window.location.pathname) {
            case '/':
                mobileTitleElement.textContent = 'Über mich';
                break;
            case '/kompetenzen.html':
                mobileTitleElement.textContent = 'Kompetenzen';
                break;
            case '/blog.html':
                mobileTitleElement.textContent = 'Blog';
                break;
            case '/kontakt.html':
                mobileTitleElement.textContent = 'Kontakt';
                break;
        }
    }

    attributeChangedCallback(name, oldValue, value) {
        if (name !== 'hide-aside') return;
        this.hideAside = !!value;
    }

    async connectedCallback() {
        await this.mountTemplate();
        this.setupNavigation();
        this.setPageTitle();
    }
}

customElements.define('portfolio-shell', PortfolioShell);
